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

# Nombramos las columnas
colnames(taquilla_precuelas) <- region

# Nombramos las filas
rownames(taquilla_precuelas) <- nombres_precuelas

# Unimos ambas matrices
taquilla_todas <- rbind(taquilla, taquilla_precuelas)

# Imprimimos la matriz final
taquilla_todas
