<?php
use PHPMailer\PHPMailer\PHPMailer;
require 'vendor/autoload.php';
    $mail = new PHPMailer;
    $mail->isSMTP();
    $mail->Host = 'smtp.hostinger.com';
    $mail->Port = 587;
    $mail->SMTPAuth = true;
    $mail->Username = 'contato@code369.com.br';
    $mail->Password = 'Code369#';
    $mail->setFrom('contato@code369.com.br', ' Mobil Argentina');
    $mail->addAddress('suportetecnico@moovelub.com', 'Cuente con nosotros');
    if ($mail->addReplyTo($_POST['email'], $_POST['name'], $_POST['phone'],  $_POST['subject'], $_POST['message'] )) {
        $mail->Subject = 'Site';
        $mail->isHTML(false);
        $mail->Body = <<<EOT
        Email: {$_POST['email']}
        Nombre: {$_POST['name']}
        Teléfono: {$_POST['phone']}
        Asunto: {$_POST['subject']}
        Mensaje: {$_POST['message']}

        EOT;
        if (!$mail->send()) {
            $msg = 'Lo sentimos, se produjo un error<br>Vuelva a intentarlo';
        } else {
            $msg = 'Su mensaje fue reenviado correctamente';
        }
    } else {
        $msg = 'Share it with us!';
    }

    echo '<script type="text/javascript">'; 
    echo 'alert("Su mensaje fue reenviado correctamente");'; 
    echo 'window.location.href = "https://ar.moovelub.com/mobil/";';
    echo '</script>';

?>
