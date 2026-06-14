# Creamos un vector
mi_vector <- c(1:10)

# Creamos una matriz
matriz <- matrix(c(1:9), ncol = 3)

# Extraemos algunos datos de mtcars
# para usarlos como un marco
marco <- mtcars[1:10,]

# Creamos la lista
mi_lista <- list(mi_vector, matriz, marco)

# Demos nombre a los elementos
names(mi_lista) <- c("Vector", "Matriz", "Marco")

# Mostremos la lista
# mi_lista

# Seleccionemos el vector
mi_lista[["Vector"]]

# Lo mismo pero diferente
mi_lista[[1]]

# De nuevo lo mismo pero diferente
mi_lista$Vector
