<?php
    $errorMessage = "";

if(!$_POST['firstName']) {
    $errorMessage = "Bitte Vornamen eintragen.";
} else {
    $firstName = $_POST['firstName'];
}

if(!$_POST['lastName']) {
    $errorMessage = "Bitte Nachnamen eintragen.";
} else {
    $lastName = $_POST['lastName'];
}

if(!$_POST['email']) {
    $errorMessage = "Bitte gültige Email-Adresse eintragen.";
} else {
    if (strstr($_POST["email"],"@") && strstr($_POST["email"],".")){
        $emailFrom = $_POST["email"];
    } else {
        $errorMessage = "Bitte gültige Email-Adresse eintragen.";
    }
}

if(!$_POST['subject']) {
    $errorMessage = "Bitte Betreff eintragen.";
} else {
    $subject = $_POST["subject"];
}

if(!$_POST['firstName']) {
    $errorMessage = "Bitte Nachricht eintragen.";
} else {
    $firstName = $_POST['firstName'];
}

if($errorMessage == "") {
    $emailTo = "weltarchiv@gmail.com";

    $subject1 = "[Form submission]" . " " + $subject;
    $subject2 = "Deine Kopie von " . $subject1;
    $message1 = $firstName . " " . $lastName . " schrieb:" . "\n\n" . $_POST['message'];
    $message2 = "Dies ist eine Kopie Ihrer Nachricht, " . $firstName . ": \n\n" . $_POST['message'];

    // send email
    $success1 = mail($emailTo, $subject1, $message1, "From:".$emailFrom);
    $success2 = mail($emailFrom, $subject2, $message2, "From:".$emailTo);

    // redirect to success page
    if ($success1 && $success2){
        echo "success";
    } else {
        goto error;
    }
} else {
    error:
    if($errorMessage == ""){
        echo "Something went wrong :(";
    } else {
        echo $errorMessage;
    }
}

?>