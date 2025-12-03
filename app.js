
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
    apiKey: "AIzaSyByGxDtUJ6VlRGLt_9xJiKCeHYEZyYO3BA",
    authDomain: "smartsensors-dbf09.firebaseapp.com",
    databaseURL: "https://smartsensors-dbf09-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "smartsensors-dbf09",
    storageBucket: "smartsensors-dbf09.firebasestorage.app",
    messagingSenderId: "367627115408",
    appId: "1:367627115408:web:24d2512cd852224d86b115",
    measurementId: "G-0WPBQNHY38"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);

// ------------------
// 2. FUNKCJA ZMIANY SEKCJI
// ------------------
function showSection(id) {
    document.querySelectorAll("section").forEach(s => s.classList.remove("visible"));
    document.getElementById(id).classList.add("visible");
}


// ------------------
// 3. WYKRESY
// ------------------
const tempChart = new Chart(document.getElementById("tempChart"), {
    type: "line",
    data: { labels: [], datasets: [{ label: "Temperatura (°C)", data: [] }] },
    options: { responsive: true }
});

const humChart = new Chart(document.getElementById("humChart"), {
    type: "line",
    data: { labels: [], datasets: [{ label: "Wilgotność (%)", data: [] }] },
    options: { responsive: true }
});

const lightChart = new Chart(document.getElementById("lightChart"), {
    type: "line",
    data: { labels: [], datasets: [{ label: "Światło (lx)", data: [] }] },
    options: { responsive: true }
});


// ------------------
// 4. ODBIÓR DANYCH Z FIREBASE W CZASIE RZECZYWISTYM
// ------------------
db.ref("data").on("value", snapshot => {
    const data = snapshot.val();
    if (!data) return;

    // Wstaw dane do głównego panelu
    document.getElementById("tempValue").innerText = data.temperature + " °C";
    document.getElementById("humValue").innerText = data.humidity + " %";
    document.getElementById("lightValue").innerText = data.light + " lx";

    // Dodaj do wykresu
    const time = new Date().toLocaleTimeString();
    tempChart.data.labels.push(time);
    humChart.data.labels.push(time);
    lightChart.data.labels.push(time);

    tempChart.data.datasets[0].data.push(data.temperature);
    humChart.data.datasets[0].data.push(data.humidity);
    lightChart.data.datasets[0].data.push(data.light);

    tempChart.update();
    humChart.update();
    lightChart.update();

    // Dodaj do historii
    const row = `
        <tr>
            <td>${time}</td>
            <td>${data.temperature}</td>
            <td>${data.humidity}</td>
            <td>${data.light}</td>
        </tr>
    `;
    document.getElementById("historyTable").innerHTML += row;
});
