#include "irifitnessfunction.h"
#include "collisionmanager.h"

/******************************************************************************/
/******************************************************************************/

CIriFitnessFunction::CIriFitnessFunction(const char* pch_name, 
                                                                 CSimulator* pc_simulator, 
                                                                 unsigned int un_collisions_allowed_per_epuck)
    :
    CFitnessFunction(pch_name, pc_simulator)
{

	/* Check number of robots */
	m_pcSimulator = pc_simulator;
	TEpuckVector* pvecEpucks=m_pcSimulator->GetEpucks();
	
	if ( pvecEpucks->size() == 0 )
	{
		printf("No Robot, so fitness function can not be computed.\n Exiting...\n");
		fflush(stdout);
		exit(0);
	}
	else if  (pvecEpucks->size()>1)
	{
		printf("More than 1 robot, and fitness is not prepared for it.\n Exiting...\n");
	}
    
	m_pcEpuck=(*pvecEpucks)[0];

	m_unNumberOfSteps = 0;
	m_fComputedFitness = 0.0;
	m_unCollisionsNumber 	= 0;
	
}

/******************************************************************************/
/******************************************************************************/

CIriFitnessFunction::~CIriFitnessFunction(){
}
/******************************************************************************/
/******************************************************************************/

double CIriFitnessFunction::GetFitness()
{    

	/* If you need to check the collisions of the robot, here are the total number of 
	 * collisions done by the robot in the simulations */
	int coll = (CCollisionManager::GetInstance()->GetTotalNumberOfCollisions());

	/* Get the fitness divided by the number of steps */
	double fit = ( m_fComputedFitness / (double) m_unNumberOfSteps ) * (1 - ((double) (fmin(coll,10.0)/10.0)));

	/* If fitness less than 0, put it to 0 */
	if ( fit < 0.0 ) fit = 0.0;

	return fit;
}

/******************************************************************************/
/******************************************************************************/
void CIriFitnessFunction::SimulationStep(unsigned int n_simulation_step, double f_time, double f_step_interval)
{
	/* See Evolutionary Robotics Book */
	/* This is the function to be implemented */
	/* f = V * ( 1 - sqrt(Delta(v)) ) * (1 - i)
	 * V relates to the maximum speed
	 * Delta(v) relates to the movement on the same direction
	 * i relates to the maximum sensor value
	 */

	/* Get actual SPEED of the left and right wheel */
	double leftSpeed = 0.0;
	double rightSpeed = 0.0;
	m_pcEpuck->GetWheelSpeed(&leftSpeed,&rightSpeed);
	leftSpeed = 0.5 + ( leftSpeed / ( 2.0 *  m_pcEpuck->GetMaxWheelSpeed()) );
	rightSpeed = 0.5 + ( rightSpeed / ( 2.0 *  m_pcEpuck->GetMaxWheelSpeed()) );

	/* Eval maximum speed partial fitness */
	double maxSpeedEval = (fabs(leftSpeed - 0.5) + fabs(rightSpeed - 0.5));

	/* Eval same direction partial fitness */
	double sameDirectionEval = 1 - sqrt(fabs(leftSpeed - rightSpeed)); //exp(-pow(fabs(leftSpeed - rightSpeed), 2)/(2*pow(0.2, 2)));

	/* Eval robot going in circles */ // otros experimentos cicleEval = 0.12
	double circleEval1 = exp(-pow(fabs(leftSpeed - rightSpeed) - 0.08, 2)/(2*pow(0.1, 2)));//-10 * pow(fabs(leftSpeed - rightSpeed) - 0.17 ,2) + 1;
	double circleEval2 = exp(-pow(fabs(leftSpeed - rightSpeed) - 0.04, 2)/(2*pow(0.1, 2)));

	/* Eval SENSORS */

	/* Where the Max PROXIMITY sensor will be stored*/
	double maxProxSensorEval 		= 0.0;
	/* Where the Max LIGHT sensor will be stored*/
	double maxLightSensorEval 	= 0.0;
	/* Where the Max BLUE LIGHT sensor will be stored*/
	double maxBlueLightSensorEval 	= 0.0;
	/* Where the Max RED LIGHT sensor will be stored*/
	double maxRedLightSensorEval 	= 0.0;
	/* Where the Max CONTACT sensor will be stored*/
	double maxContactSensorEval = 0.0;

	/* Where the GROUND MEMORY will be stored */
	double* groundMemory;
	/* Where the GROUND will be stored */
	double* ground;
	/* whre the BATTERY will be sotored */
	double *battery;
	/* whre the BLUE BATTERY will be sotored */
	double *blueBattery;
	/* whre the RED BATTERY will be sotored */
	double *redBattery;

	double blueLightS1=0;
	double blueLightS2=0;

	double lightS5=0;
	double lightS6=0;

	double redLightS5=0;
	double redLightS6=0;

	int blueLightOn = 0;
	int redLightOn = 0;
	int lightOn = 0;

	/* Auxiluar variables */
	unsigned int unThisSensorsNumberOfInputs; 
	double* pfThisSensorInputs; 
	
	/* Go in all the sensors */
	TSensorVector vecSensors = m_pcEpuck->GetSensors();
	for (TSensorIterator i = vecSensors.begin(); i != vecSensors.end(); i++)
	{
		/* Check type of sensor */
		switch ( (*i)->GetType() )
		{
			/* If sensor is PROXIMITY */
			case SENSOR_PROXIMITY:
				/* Get the number of inputs */
				unThisSensorsNumberOfInputs = (*i)->GetNumberOfInputs();
				/* Get the actual values */
				pfThisSensorInputs = (*i)->GetComputedSensorReadings();

				/* For every input */
				for (int j = 0; j < unThisSensorsNumberOfInputs; j++)
				{
					/* If reading bigger than maximum */
					if ( pfThisSensorInputs[j] > maxProxSensorEval )
					{	
						/* Store maximum value */
						maxProxSensorEval = pfThisSensorInputs[j];
					}
				}
				break;

			/* If sensor is GROUND_MEMORY */
			case SENSOR_GROUND_MEMORY:
				/* Get the actual value */
				groundMemory = (*i)->GetComputedSensorReadings();
				break;
	
			/* If sensor is GROUND */
			case SENSOR_GROUND:
				/* Get actual values */
				ground = (*i)->GetComputedSensorReadings();
				break;	
			/* If sensor is LIGHT */
			case SENSOR_REAL_LIGHT:
				/* Get number of inputs */
				unThisSensorsNumberOfInputs = (*i)->GetNumberOfInputs();
				/* Get the actual values */
				pfThisSensorInputs = (*i)->GetComputedSensorReadings();

				/* For every input */
				for (int j = 0; j < unThisSensorsNumberOfInputs; j++)
				{
					/* If reading bigger than maximum */
					if ( pfThisSensorInputs[j] > maxLightSensorEval )
					{	
						/* Store maximum value */
						maxLightSensorEval = pfThisSensorInputs[j];
					}
					if (j==5)
						lightS5 = pfThisSensorInputs[j];
					else if (j==6)
						lightS6 = pfThisSensorInputs[j];
				}
				break;
			case SENSOR_REAL_BLUE_LIGHT:
				unThisSensorsNumberOfInputs = (*i)->GetNumberOfInputs();
				pfThisSensorInputs = (*i)->GetComputedSensorReadings();

				for (int j = 0; j < unThisSensorsNumberOfInputs; j++)
				{
					if ( pfThisSensorInputs[j] > maxBlueLightSensorEval )
					{	
						maxBlueLightSensorEval = pfThisSensorInputs[j];
					}
					/////////////////////////////////////////////////////CAMBIAR ESTO/////////////////////////////////
					if (j==1)
						blueLightS1 = pfThisSensorInputs[j];
					else if (j==2)
						blueLightS2 = pfThisSensorInputs[j];
				}
				break;
			
			case SENSOR_REAL_RED_LIGHT:
				unThisSensorsNumberOfInputs = (*i)->GetNumberOfInputs();
				pfThisSensorInputs = (*i)->GetComputedSensorReadings();

				for (int j = 0; j < unThisSensorsNumberOfInputs; j++)
				{
					if ( pfThisSensorInputs[j] > maxRedLightSensorEval )
					{	
						maxRedLightSensorEval = pfThisSensorInputs[j];
					}
					if (j==5)
						redLightS5 = pfThisSensorInputs[j];
					else if (j==6)
						redLightS6 = pfThisSensorInputs[j];
				}
				break;

			/* If sensor is BATTERY */
			case SENSOR_BATTERY:
         battery = (*i)->GetComputedSensorReadings();
				 break;
			
			case SENSOR_BLUE_BATTERY:
				blueBattery = (*i)->GetComputedSensorReadings();
				break;
			
			case SENSOR_RED_BATTERY:
				redBattery = (*i)->GetComputedSensorReadings();
				break;
			
			/* If sensor is CONTACT */
			case SENSOR_CONTACT:
				/* Get number of inputs */
				unThisSensorsNumberOfInputs = (*i)->GetNumberOfInputs();
				/* Get actual values */
				pfThisSensorInputs = (*i)->GetComputedSensorReadings();

				/* For every input */
				for (int j = 0; j < unThisSensorsNumberOfInputs; j++)
				{
					/* If reading bigger than maximum */
					if ( pfThisSensorInputs[j] > maxContactSensorEval )
					{
						/* Store maximum value */
						maxContactSensorEval = pfThisSensorInputs[j];
					}
				}
				break;
		}
	}
	
	/* START - FROM HERE YOU NEED TO CREATE YOUR FITNESS */	
	/* Acoto circleEval por abajo */
	if (circleEval1 < 0.0 || circleEval2 < 0.0)
	{
		circleEval1 = circleEval2 = 0.0;
	}
	maxProxSensorEval = 1 - maxProxSensorEval;
	
	/* FITNESS EXPERIMENTO 1 */
	
	/*
	if(maxBlueLightSensorEval > 0.0){

		fitness = maxSpeedEval * circleEval1 * maxProxSensorEval * (leftSpeed * rightSpeed); //CIRCULOS

	} else {

		// Max Speed * Same Direction * Min Prox * go forwards 
		fitness = maxSpeedEval * sameDirectionEval * maxProxSensorEval * (leftSpeed * rightSpeed);// RECTO
	}

	*/
	/*END FITNESS EXPERIMENTO 1 */



	/* FITNESS EXPERIMENTO 2 */
	/*
	if(maxBlueLightSensorEval > 0.0){

		fitness = maxSpeedEval *  circleEval2 * (leftSpeed * rightSpeed) * (blueLightS0 + blueLightS7)/2;

	} else {

		fitness = maxSpeedEval * sameDirectionEval * maxProxSensorEval * (leftSpeed * rightSpeed);// RECTO
	}

	*/
	/*END FITNESS EXPERIMENTO 2 */

	/* FITNESS EXPERIMENTO 3 */
	
	if(maxBlueLightSensorEval > 0.0){
		blueLightOn = 1;

		//fitness = maxSpeedEval *  circleEval2 * (leftSpeed * rightSpeed) * (blueLightS1 + blueLightS2)/2;

	} else if (maxRedLightSensorEval > 0.0) {
		redLightOn = 1;

		//fitness = maxSpeedEval * sameDirectionEval * (leftSpeed * rightSpeed) * maxProxSensorEval * (redLightS0 +redLightS7)/2 * redBattery[0];
	}

	else if (maxLightSensorEval > 0.0) {
		lightOn = 1;

		//fitness = maxSpeedEval * sameDirectionEval * (leftSpeed * rightSpeed) *  maxProxSensorEval  * (lightS0 + lightS7)/2 *  battery[0];
	}
	double blue = circleEval2 * (blueLightS1 + blueLightS2)/2;
	double red = circleEval1 * (redLightS5 + redLightS6)/2;
	double yellow = circleEval1 * (lightS5 + lightS6)/2;

	double fitness = maxSpeedEval * (leftSpeed * rightSpeed) *  (blueLightOn * blue + redLightOn * red + lightOn * yellow );
	
	/*END FITNESS EXPERIMENTO 3 */

	/* FITNESS EXPERIMENTO 4 */
	/*
	if(maxBlueLightSensorEval > 0.0){
		blueLightOn = 1;

		//fitness = maxSpeedEval *  circleEval2 * (leftSpeed * rightSpeed) * (blueLightS1 + blueLightS2)/2;

	} else if (maxRedLightSensorEval > 0.0) {
		redLightOn = 1;

		//fitness = maxSpeedEval * sameDirectionEval * (leftSpeed * rightSpeed) * maxProxSensorEval * (redLightS0 +redLightS7)/2 * redBattery[0];
	}

	else if (maxLightSensorEval > 0.0) {
		lightOn = 1;

		//fitness = maxSpeedEval * sameDirectionEval * (leftSpeed * rightSpeed) *  maxProxSensorEval  * (lightS0 + lightS7)/2 *  battery[0];
	}
	double blue = circleEval2 * (blueLightS1 + blueLightS2)/2;
	double red = (redLightS0 + redLightS7)/2 * redBattery[0];
	double yellow = (lightS0 + lightS7)/2 *  battery[0];

	fitness = maxSpeedEval * (leftSpeed * rightSpeed) *  (blueLightOn * blue + sameDirectionEval * maxProxSensorEval* (redLightOn * red + lightOn * yellow ));
	*/
	/*END FITNESS EXPERIMENTO 4 */

	m_unNumberOfSteps++;
	m_fComputedFitness += fitness;

	/* Get Collisions */
	int nContact = 0;
	CContactSensor* m_seContact = (CContactSensor*) m_pcEpuck->GetSensor(SENSOR_CONTACT);
	double* contact = m_seContact->GetSensorReading(m_pcEpuck);
	for ( int j = 0 ; j < m_seContact->GetNumberOfInputs() ; j++)
	{
		if(contact[j] > 0.0) 
			nContact=1;
	} 

	if ( nContact == 1 )
		m_unCollisionsNumber++;
}

/******************************************************************************/
/******************************************************************************/
