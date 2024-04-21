<?php
session_start();

// Check if agent number is set in session
if(!isset($_SESSION['agent_nr'])) {
    $_SESSION['msg'] = "You must log in first";
    header('location: login.php');
    exit();
}

// Handle logout
if(isset($_GET['logout'])) {
    session_destroy();
    unset($_SESSION['agent_nr']);
    header("location: login.php");
    exit();
}

// Include server.php for database connection
include('server.php');

// Fetch agent number from session
$agent_nr = $_SESSION['agent_nr'];
$index = $_GET['index']; // Get the index from the URL parameter

// Fetch client details based on agent number and index
$query ="SELECT * FROM clients_2 WHERE agent = (SELECT agent_nr FROM agents WHERE agent_nr='$agent_nr') AND visit_date='$index'-1";
$result = mysqli_query($db, $query);
$clients = mysqli_fetch_all($result, MYSQLI_ASSOC);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Client Details</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body style="background-color: #B5C18E;">
    <div class="content">
        <?php if (isset($_SESSION['success'])): ?>
            <div class="error success">
                <h3><?php echo $_SESSION['success']; unset($_SESSION['success']); ?></h3>
            </div>
        <?php endif ?>

        <?php if (isset($_SESSION['agent_nr'])): ?>
      


<h1 style="text-align: center; margin-top: 50px;">Appointments:</h1>

            <?php if(!empty($clients)): ?>
                <ul>
                    <?php foreach ($clients as $client): ?>
<div class="client-details">
    <div class="detail">
        <span class="label">City:</span>
        <span class="value"><?php echo $client['city']; ?></span>
    </div>
    <div class="detail">
        <span class="label">County:</span>
        <span class="value"><?php echo $client['county']; ?></span>
    </div>
    <div class="detail">
        <span class="label">Sold:</span>
        <span class="value"><?php echo $client['sold']; ?>$</span>
    </div>
    <div class="detail">
        <span class="label">Category:</span>
        <span class="value"><?php echo $client['group']; ?></span>
    </div>
</div>
<div class="client-details">
    <div class="detail">
        <span class="label">City:</span>
        <span class="value">Brasov</span>
    </div>
    <div class="detail">
        <span class="label">County:</span>
        <span class="value">Brasov</span>
    </div>
    <div class="detail">
        <span class="label">Sold:</span>
        <span class="value">167850$</span>
    </div>
    <div class="detail">
        <span class="label">Category:</span>
        <span class="value">MEDIUM</span>
    </div>
</div>

                    <?php endforeach; ?>
                </ul>
        <?php else: ?>
		<div class="client-details">
			 <div class="detail">
                <h1 style="text-align: center; margin-top: 50px;">No client details found for the selected index.</h1>
				 </div>
	</div>
            <?php endif; ?>
   
           
        <?php endif; ?>
    </div>
	 <div class="bottom-line">
        <h1 style="margin-left:20px;">B2B Retailing - Solutions for you!</h1>
        <h1 style="margin-right:20px;">email: b2bsolutions.cluj@gmail.com</h1>
    </div>

</body>
</html>
