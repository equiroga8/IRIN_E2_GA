En la carpeta actual se puede encontrar en primer lugar un conjunto de directorios correspondientes a los geneticDataFiles de cada uno de nuestros experimentos. Tambien podemos encontrar los directorios correspondientes a los outputFiles de nuestros experimentos. 

Más adelante podemos ver los objetos de las luces azul, amarilla y roja con sus correspondientes modificaciones.

Se incluye tambien el archivo textneuronexp.cpp que es el necesario para llevar a cabo nuestro experimento.

Nuestras distientas funciones de fitness empleadas se encuentran en el archivo irifitnessfunction.cpp. Estas funciones se encuentran en la parte final del código y están comentadas para poder usar solo la que nos haga falta en nuestro caso dependiendo del experimento elegido. Se incluye también irifitnessfunction.h.

Por último se incluyen los paramFiles correspondientes a cada uno de nuestro experimentos.



Pasos para realizar los experimentos:

0) En primer lugar introduciremos en nuestro sumilador los archivos bluelightobject.cpp, lightobject.cpp, redlightobject.cpp, testneuronexp.cpp, irifitnessfunction.cpp e irifitnessfunction.h. Estos archivos ya serán validos para todos los experimentos.

EXP1) Para ejecutar el experimento 1:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles1 (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo1.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente al EXP1 (al final de SimulationStep)
	-En irifitnessfunction, en GetFitness, descomentar la última parte de la linea donde se calcula la variable fit.
	-Ejecutamos ./irsim -E 21 -p paramFiles/paramFileNeuronEvo1.txt -c (habiendo ejecutado make previamente)

EXP2) Para ejecutar el experimento 2A:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles2A (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo2.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente al EXP2A y EXP2B (al final de SimulationStep)
	-En irifitnessfunction, en GetFitness, descomentar la última parte de la linea donde se calcula la variable fit.
	-Ejecutamos ./irsim -E 21 -p paramFiles/paramFileNeuronEvo2.txt -c (habiendo ejecutado make previamente)

EXP2B) Para ejecutar el experimento 2B:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles2B (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo2B.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente al EXP2A y EXP2B (al final de SimulationStep)
	-En irifitnessfunction, en GetFitness, descomentar la última parte de la linea donde se calcula la variable fit.
	-Ejecutamos ./irsim -E 21 -p paramFiles/paramFileNeuronEvo2B.txt -c (habiendo ejecutado make previamente)

EXP3) Para ejecutar el experimento 3:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles3 (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo3.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente a EXP 3, 4 y 5 (al final de SimulationStep)
	-Ejecutamos ./irsim -E 21 -p paramFiles/paramFileNeuronEvo3.txt -c (habiendo ejecutado make previamente)

EXP4) Para ejecutar el experimento 4:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles4 (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo4.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente a EXP 3, 4 y 5 (al final de SimulationStep)
	-Ejecutamos ./irsim -E 24 -p paramFiles/paramFileNeuronEvo4.txt -c (habiendo ejecutado make previamente)

EXP4) Para ejecutar el experimento 5:
	-Introducimos en nuestro simulador los archivos del directorio geneticDataFiles5 (en geneticDataFiles)
	-Introducimos en nuestro simulador el archivo paramFileNeuronEvo5.txt (en paramFiles)
	-En irifitnessfunction dejamos sin comentar solo la parte correspondiente a EXP 3, 4 y 5 (al final de SimulationStep)
	-Ejecutamos ./irsim -E 24 -p paramFiles/paramFileNeuronEvo5.txt -c (habiendo ejecutado make previamente)










