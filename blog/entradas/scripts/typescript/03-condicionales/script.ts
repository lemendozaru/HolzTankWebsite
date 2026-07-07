// Definimos la distancia
let distancia = 250;

// Definimos el combustible
let combustible = 100;

// Definimos la condición de poder llegar siempre y
// cuando la distancia esté entre 100 y 200
let distanciaCondicion = distancia <= 200 && distancia >= 100;

// ¿El motor está funcionando?
let motorFuncionando = true;

// Primera evaluación: no llegará
if (!motorFuncionando || distancia > 200) {
    console.log("No llegaremos")
}

// Segunda evaluación: llegará por distancia mediana y
// combustible suficiente
else if (distanciaCondicion && combustible >= 100) {
    console.log("Llegaremos")
}

// Tercera evaluación: llegará por distancia corta y
// poco combustible
else if (distancia < 100 && combustible > 25) {
    console.log("Llegaremos pronto")
}
