#!/bin/bash

# Fuentes
archivos_fuente=("HEM_A" "GFP_A" "ACE2_A")

# Residuos
residuos=("LYS" "ARG" "HIS" "GLU" "ASP")

# Archivo .csv de salida
output="residuos_cargados.csv"

# Crea encabezado
echo "aas;HEM;GFP;ACE2" > $output


for res in "${residuos[@]}"; do

	# Linea inicial
	echo -n "${res}" >> $output
	
	# Lee cada proteina
	for fuente in "${archivos_fuente[@]}"; do
	
		# Contar CA del residuo SIN archivos intermedios
		conteo_lineas=$(grep "CA" ${fuente}.pdb | grep "${res}" | wc -l)
		
		# Agregar conteo
		echo -n ";${conteo_lineas}" >> $output
	done
	
	# Nueva linea
	echo "" >> $output
done
