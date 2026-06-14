# Creamos los vectores
nombre <-
  c("Mercurio", "Venus", "Tierra", "Marte", "Júpiter", "Saturno",
    "Urano", "Neptuno")
tipo <-
  c("Terrestre", "Terrestre", "Terrestre", "Terrestre", "Gaseoso",
    "Gaseoso", "Gaseoso", "Gaseoso")
diametro <- c(0.382, 0.949, 1, 0.532, 11.209, 9.449, 4.007, 3.883)
rotacion <- c(58.64, -243.02, 1, 1.03, 0.41, 0.43, -0.72, 0.67)
anillos <- c(FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE)

# Creamos el marco de datos
planetas <- data.frame(nombre, tipo, diametro, rotacion, anillos)

# Mostramos el marco
planetas[order(planetas$diametro),]
