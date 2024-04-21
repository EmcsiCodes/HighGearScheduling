<?php
$errors = array();

// Connect to the database
$db = mysqli_connect('localhost', 'root', '', 'b2b_retail');
if (!$db) {
    echo "connection error";
}

// Handle form submission
if (isset($_POST['login_user'])) {
    // Get form data
    $username = mysqli_real_escape_string($db, $_POST['agent_nr']);
    $password = mysqli_real_escape_string($db, $_POST['password']);

    // Validate form data
    if (empty($username)) {
        array_push($errors, "Username is required");
    }
    if (empty($password)) {
        array_push($errors, "Password is required");
    }

    // If there are no validation errors, attempt to log in
    if (count($errors) == 0) {
        $query = "SELECT * FROM agents WHERE agent_nr='$username' AND password='$password'";
        $results = mysqli_query($db, $query);
        if (mysqli_num_rows($results) == 1) {
            // Log in successful
            $_SESSION['agent_nr'] = $username;
            $_SESSION['success'] = "Login Successful";
            header('location: index.php');
        } else {
            // Log in failed
            array_push($errors, "Wrong username/password combination");
        }
    }
}
?>
