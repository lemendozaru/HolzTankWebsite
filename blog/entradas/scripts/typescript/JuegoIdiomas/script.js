// Definimos el objeto para la pregunta
let pregunta = {
    nombre: "cat",
    opciones: ["perro", "gato", "pájaro", "pescado"],
    correcta: 1
};

function inicio() {
    // obtener opciones
    let alts = document.querySelectorAll(".opcion");
    // agregar manejadores de eventos
    alts.forEach(function(element, index) {
        element.addEventListener("click", function() {
            // verificar respuesta correcta
            console.log("verificar respuesta correcta")
        });
    });

    // Muestra primera pregunta
    mostrarPregunta(pregunta);
}

function mostrarPregunta(p) {
    // Muestra el nombre de pregunta
    let nombreDiv = document.getElementById("nombre");
    nombreDiv.textContent = p.nombre;

    // Muestra alternativas
    let alts = document.querySelectorAll(".opcion");
    alts.forEach(function(elements, index) {
        elements.textContent = p.opciones[index];
    });
}

inicio();
