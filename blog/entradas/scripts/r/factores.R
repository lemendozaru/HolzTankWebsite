# Creamos el vector con el sexo
sexo <- c("Male", "Female", "Female", "Male", "Male")

# Codificamos el vector como factor
sexo_factor <- factor(sexo)

# Mostramos el factor
# sexo_factor

# Vector con las temperaturas
temperaturas <- c("Alta", "Baja", "Alta", "Baja")

# Factor ordenado de las temperaturas
temperaturas_factor <-
  factor(temperaturas, ordered = TRUE, levels = c("Baja", "Media", "Alta"))

# Mostramos el factor
# temperaturas_factor

# Reasignamos niveles
levels(sexo_factor) <- c("Femenino", "Masculino")

# Mostramos el nuevo vector
# sexo_factor

# Resumen del factor
summary(sexo_factor)
