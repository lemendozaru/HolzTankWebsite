# Creamos los vectores
new_hope <- c(460.998, 314.4)
empire_strikes <- c(290.475, 247.900)
return_jedi <- c(309.306, 165.8)

# Creamos la matriz
taquilla <- matrix(c(new_hope, empire_strikes, return_jedi),
                   byrow = TRUE, nrow = 3)

# Nombremos los elementos de la matriz
# Columnas
region <- c("US", "Non-US")

# Filas
nombres <- c("A New Hope", "The Empire Strikes Back", "Return of the Jedi")

# Nombramos columnas
colnames(taquilla) <- region

# Nombramos filas
rownames(taquilla) <- nombres

# Imprimimos la matriz
# taquilla

# Calculemos la taquilla por película
total <- rowSums(taquilla)

# Mostremos el resultado
# total

# Agreguemos este vector como una nueva columna
taquilla_total <- cbind(taquilla, total)

# Imprimimos la nueva matriz
# taquilla_total

# Creamos la matriz con las precuelas
taquilla_precuelas <- matrix(c(474.5, 552.5, 310.7, 338.7, 380.3, 468.5),
                             byrow = TRUE, nrow = 3)

# Creamos el vector con los nombres
nombres_precuelas <- c("The Phantom Menace", "Attack of the Clones",
                       "Revenge of the Sith")

# Nombramos las filas
rownames(taquilla_precuelas) <- nombres_precuelas

# Unimos ambas matrices
taquilla_todas <- rbind(taquilla, taquilla_precuelas)

# Imprimimos la matriz final
# taquilla_todas

# Calculemos el total de taquilla por región
# taquilla_region <- colSums(taquilla_todas)

# Mostremos el resultado
# taquilla_region

# Mostremos solo la taquilla fuera de los EU
# taquilla_todas[,2]

# Calculemos solo la media de esa taquilla
# mean(taquilla_todas[,2])

# Seleccionemos solo la taquilla de las primeras dos
# taquilla_todas[1:2,2]

# Calculemos su media
# mean(taquilla_todas[1:2,2])

# Para calcular la asistencia
# dividamos entre 5
# asistentes <- taquilla_todas / 5

# Mostremos el resultado
# asistentes

# Creamos la matriz con los precios
# precios <- matrix(c(5,5,6,6,7,7,4,4,4.5,4.5,4.9,4.9),
#                  byrow = TRUE, nrow = 6)

# Dividamos la primera entre la segunda
# asistentes_reales <- taquilla_todas / precios

# Mostremos los asistentes reales
# asistentes_reales

# Calculemos y agreguemos la suma de columnas
taquilla_todas <- rbind(taquilla_todas, colSums(taquilla_todas))

# Ahora calculemos la suma de filas
taquilla_todas <- cbind(taquilla_todas, rowSums(taquilla_todas))

# Mostremos
taquilla_todas
