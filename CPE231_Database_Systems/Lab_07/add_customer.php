<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <title>Add customer - Yee NetBank</title>
</head>
<body>
  <form action="add_customer_post.php" method="post">
    <div>
      <label for="fname">First name: </label>
      <input type="text" name="fname" id="fname"/>
    </div>
    <div>
      <label for="lname">Last name: </label>
      <input type="text" name="lname" id="lname"/>
    </div>
    <div>
      <label>Gender: </label>
      <input type="radio" name="gender" id="genderM" value="M">
      <label for="genderM">Male</label>
      <input type="radio" name="gender" id="genderF" value="M">
      <label for="genderF">Female</label>
      <input type="radio" name="gender" id="genderU" value="U">
      <label for="genderU">Undefined</label>
    </div>
    <div>
      <label for="address">Address: </label>
      <br />
      <textarea name="address" id="address" cols="30" rows="10"></textarea>
    </div>
    <div>
      <label for="date">Date of birth: </label>
      <input type="date" name="birthdate" id="birthdate">
    </div>
    <div>
      <label for="citizenId">Citizen ID</label>
      <input type="text" name="citizenId" id="citizenId" length="13">
    </div>
    <div>
      <label for="phone">Phone number</label>
      <input type="text" name="phone" id="phone" length="13">
    </div>

    <div>
      <input type="submit" value="Submit">
    </div>
  </form>
</body>
</html>