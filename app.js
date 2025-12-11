/* ====== FIREBASE CONFIG ====== */
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

firebase.initializeApp(firebaseConfig);
const db = firebase.database();

/* ========= ГРАФИКИ =========== */

function createChart(ctx, label, min, max, color) {
    return new Chart(ctx, {
    type: "line",
    data: { labels: [], datasets: [{ label: label, data: [], borderColor: color, tension: 0.25 }] },
    options: {
        responsive: true,
        scales: {
        y: { min: min, max: max },
        x: { ticks: { autoSkip: true, maxTicksLimit: 10 } }
        }
    }
    });
}

let chartTemp = null;
let chartHum = null;
let chartLight = null;

if (document.getElementById("chartTemp")) {

    // Temperatura – STATYCZNA OŚ Y (-5…60)
    chartTemp = new Chart(document.getElementById("chartTemp"), {
        type: "line",
        data: { labels: [], datasets: [{ label: "Temperatura", data: [], borderColor: "red", tension: 0.25 }] },
        options: {
            responsive: true,
            scales: {
                y: { min: -5, max: 60 },          // statyczne
                x: { ticks: { autoSkip: true, maxTicksLimit: 10 } }
            }
        }
    });

    // Wilgotność – STATYCZNA OŚ Y (0…100)
    chartHum = new Chart(document.getElementById("chartHum"), {
        type: "line",
        data: { labels: [], datasets: [{ label: "Wilgotność", data: [], borderColor: "blue", tension: 0.25 }] },
        options: {
            responsive: true,
            scales: {
                y: { min: 0, max: 100 },           // statyczne
                x: { ticks: { autoSkip: true, maxTicksLimit: 10 } }
            }
        }
    });

    // Światło – DYNAMICZNA OŚ Y
    chartLight = new Chart(document.getElementById("chartLight"), {
        type: "line",
        data: { labels: [], datasets: [{ label: "Światło", data: [], borderColor: "orange", tension: 0.25 }] },
        options: {
            responsive: true,
            scales: {
                y: { beginAtZero: true },          // DYNAMICZNE – bez min/max!
                x: { ticks: { autoSkip: true, maxTicksLimit: 10 } }
            }
        }
    });
}


/* ========= ОБНОВЛЕНИЕ ПО ДАННЫМ ========= */

db.ref("latest").on("value", snap => {
    const data = snap.val();
    if (!data) return;

    if (document.getElementById("tempValue")) {
    document.getElementById("tempValue").textContent = data.temperature + " °C";
    document.getElementById("humValue").textContent = data.humidity + " %";
    document.getElementById("lightValue").textContent = data.light + " lx";
    }

    if (chartTemp) {
    const now = new Date().toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" });
    chartTemp.data.labels.push(now);
    chartTemp.data.datasets[0].data.push(data.temperature);
    chartHum.data.labels.push(now);
    chartHum.data.datasets[0].data.push(data.humidity);
    chartLight.data.labels.push(now);
    chartLight.data.datasets[0].data.push(data.light);
    chartTemp.update(); chartHum.update(); chartLight.update();
    }
});

/* ========= ИСТОРИЯ (7 ДНЕЙ) ========= */

if (document.getElementById("historyTable")) {

  const weekAgo = Date.now() - 7 * 24 * 3600 * 1000;

    db.ref("readings")
    .orderByChild("timestamp")
    .startAt(weekAgo)
    .on("child_added", snap => {

        const r = snap.val();
        if (!r) return;

        const tr = document.createElement("tr");
        tr.innerHTML = `
        <td>${new Date(r.timestamp).toLocaleString()}</td>
        <td>${r.temperature}</td>
        <td>${r.humidity}</td>
        <td>${r.light}</td>
        `;
        document.getElementById("historyTable").appendChild(tr);
    });
}


/* ========= ОТПРАВКА EMAIL ИЗ USTAWIENIA ========= */

if (document.getElementById("emailForm")) {
    document.getElementById("emailForm").addEventListener("submit", async (e) => {
    e.preventDefault();

    const email = document.getElementById("email").value;
    document.getElementById("emailStatus").textContent = "Wysyłanie...";

    const response = await fetch("https://us-central1-smartsensors-dbf09.cloudfunctions.net/sendEmail", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ email })
    });

    if (response.ok) {
        document.getElementById("emailStatus").textContent = "Wysłano!";
    } else {
        document.getElementById("emailStatus").textContent = "Błąd wysyłania.";
    }
    });
}
