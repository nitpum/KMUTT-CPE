<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <title>Add customer - Yee NetBank</title>
</head>
<body>
  <?php
    /* init connection */
    $conn = mysqli_connect(
      'localhost',
      'root',
      '',
      'bank'
    );
    
    /* check connection */
    if(mysqli_connect_error()) {
      echo 'database connection failed' . mysqli_connect_error();
      exit();
    }

    if(
      !isset($_POST['fname']) ||
      !isset($_POST['lname']) ||
      !isset($_POST['gender']) ||
      !isset($_POST['address']) ||
      !isset($_POST['birthdate']) ||
      !isset($_POST['citizenId']) ||
      !isset($_POST['phone'])
    ) { 
      echo 'Not Acceptable';
      exit();
    }

    $fname     = $_POST['fname'];
    $lname     = $_POST['lname'];
    $gender    = $_POST['gender'];
    $address   = $_POST['address'];
    $birthdate = $_POST['birthdate'];
    $citizenId = $_POST['citizenId'];
    $phone     = $_POST['phone'];

    /* insert */
    $sql = "INSERT INTO customer (fname, lname, gender, address, birthdate, citizenId, phone) VALUES ('".$fname."', '".$lname."', '".$gender."', '".$address."', '".$birthdate."', '".$citizenId."', '".$phone."')";
    if (!mysqli_query($conn, $sql)) {
        die('Error: ' . mysqli_error($conn));
    }

    echo 'Insert ' . $fname . ' ' . $lname . ' successfully!';

    mysqli_close($conn);
  ?>

  <a href="add_customer.php">back</a>
</body>;
</html>