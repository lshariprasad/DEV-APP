// -------- ONLINE / OFFLINE STATUS --------
function updateNetworkStatus() {
  const status = document.getElementById("network-status");

  if (!status) return;

  if (navigator.onLine) {
    status.innerText = "🟢 Online Mode";
    status.style.color = "green";
  } else {
    status.innerText = "🔴 Offline Mode";
    status.style.color = "red";
    alert("You are offline. App is running in offline mode.");
  }
}

window.addEventListener("load", updateNetworkStatus);
window.addEventListener("online", updateNetworkStatus);
window.addEventListener("offline", updateNetworkStatus);

// -------- SIMPLE FORM VALIDATION --------
function validateForm() {
  const soil = document.getElementById("soil").value;
  const temp = document.getElementById("temp").value;

  if (soil < 0 || soil > 100) {
    alert("Soil moisture must be between 0 and 100%");
    return false;
  }

  if (temp < -10 || temp > 60) {
    alert("Temperature value looks unrealistic");
    return false;
  }

  return true;
}
