# Ganancias en el póker
poker <- c(140, -50, 20, -120, 240)

# Ganancias en la ruleta
ruleta <- c(-24, -50, 100, -350, 10)

# Vector con los nombres de los días
dias_semana <- c("Lunes", "Martes", "Miércoles", "Jueves", "Viernes")

# Asignar días como nombres a ambos vectores
names(poker) <- dias_semana
names(ruleta) <- dias_semana

# Imprimir ambos vectores
# poker
# ruleta

# Sumar los totales diarios de ambos vectores
total_diario <- poker + ruleta
total_diario

total_poker <- sum(poker)
total_ruleta <- sum(ruleta)

total_semanal <- total_poker + total_ruleta
print(paste("Total por semana: ", total_semanal))
