<?php include('server.php')?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Agent Login</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    
</head>
<body class="body-login">
    
    <div class="container">
        <div class="login-container">
            <h1 style="font-size:350%">Agent Login</h1>
        </div>
        
        <form method="post" action="index.php">
            <div class="input-group"  title="Enter your Agent ID">
                <!-- <label>Agent ID:</label> -->
                <input type="text" name="agent_nr" placeholder="Your ID">
            </div>

            <div class="input-group"  title="Enter your password">
                <!-- <label>Password:</label> -->
                <input type="password" name="password" placeholder="Password">
            </div>

            <div class="input-group-button">
                <button type="submit" class="btn" name="login_user">Login</button>
            </div>
        </form>
    </div>

    <div class="bottom-line">
        <h1 style="margin-left:20px;">B2B Retailing - Solutions for you!</h1>
        <h1 style="margin-right:20px;">email: b2bsolutions.cluj@gmail.com</h1>
    </div>

</body>
</html>