import sqlite3
import requests

DB_NAME = "database.db"

def get_unsynced_data():
    """
    Fetch records that are not yet synced
    """
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    cursor.execute("""
        SELECT id, soil_moisture, temperature, irrigation_status, disease_status
        FROM farmer_data
        WHERE synced = 0
    """)

    rows = cursor.fetchall()
    conn.close()
    return rows


def mark_as_synced(record_id):
    """
    Mark a record as synced after successful upload
    """
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    cursor.execute("""
        UPDATE farmer_data
        SET synced = 1
        WHERE id = ?
    """, (record_id,))

    conn.commit()
    conn.close()


def sync_to_server(server_url):
    """
    Push offline data to online server
    """
    unsynced_data = get_unsynced_data()

    if not unsynced_data:
        return "No data to sync"

    for row in unsynced_data:
        record_id, soil, temp, irrigation, disease = row

        payload = {
            "soil_moisture": soil,
            "temperature": temp,
            "irrigation_status": irrigation,
            "disease_status": disease
        }

        try:
            response = requests.post(server_url, json=payload, timeout=5)

            if response.status_code == 200:
                mark_as_synced(record_id)

        except requests.exceptions.RequestException:
            return "Server not reachable"

    return "Sync completed successfully"
# Example usage:
# result = sync_to_server("https://example.com/api/sync")   