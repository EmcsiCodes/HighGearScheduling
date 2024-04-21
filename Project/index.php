<?php
session_start();
if(!isset($_SESSION['agent_nr']))
{
	$_SESSION['msg']="You must log in first";
	header('location:login.php');
}
if(isset($_GET['logout']))
{
	session_destroy();
	unset($_SESSION['agent_nr']);
	header("location: login.php");
}

include('server.php');

$agent_nr = $_SESSION['agent_nr'];
$query ="SELECT * FROM clients WHERE agent = (SELECT agent_nr FROM agents WHERE agent_nr='$agent_nr')";
$result = mysqli_query($db, $query);
$clients = mysqli_fetch_all($result, MYSQLI_ASSOC);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Agent Calendar</title> 
	
    <link rel="stylesheet" type="text/css" href="styles.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>
<body  class="content">
    <div>
        <?php if (isset($_SESSION['success'])): ?>
            <div class="error success">
                <h3><?php echo $_SESSION['success']; unset($_SESSION['success']); ?></h3>
            </div>
        <?php endif ?>
            
            <div class="table-container">   
                <?php if (isset($_SESSION['agent_nr'])): ?>
                <h3 style="position: absolute; top: 1vh; left: 2vw;">Your agent id: <?php echo $_SESSION['agent_nr']; ?></h3>
                <p class="logout-button-container"><a href="index.php?logout='1'" style="color:red;">Logout</a></p>

                <h1 style="position:absolute; top: 12vh; left: 50%; transform: translateX(-50%);">Calendar:</h1>
                <table class="calendar">
                    <thead>
                    <tr>
                    <th style="background-color: #B5C18E" colspan="7"><strong>MAY</strong></th>
                    </tr>
                        <tr>
                            <th>Sun</th>
                            <th>Mon</th>
                            <th>Tue</th>
                            <th>Wed</th>
                            <th>Thu</th>
                            <th>Fri</th>
                            <th>Sat</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                        // Generate the calendar starting from May 1st
                        $startDate = strtotime('2023-05-01'); // May 1st, 2023
                        $endDate = strtotime('+90 days', $startDate); // 90 days after May 1st
                        $counter=1;
                        echo "<tr>";
                        for ($i = 0; $i < 35; $i++) {
                            $currentDate = strtotime("+$i days", $startDate);
                            $dayOfWeek = date('D', $currentDate);
                            $dateString = date('M d, Y', $currentDate);

                            // Start a new row every Sunday
                        
                            echo "<td";
                            if($i>2 && $i<34)
                            {
                            echo " data-href=\"client_details.php?agent=" . $_SESSION['agent_nr'] . "&index=" . ($counter) . "\"";
                            }
                            echo">";
                            if($i>2 && $i<34)
                            {
                                    echo $counter;
                                    $counter++;
                            } 
                            if ($dayOfWeek == 'Sun' && $i != 0 && $i<34) {
                                echo "</tr><tr>";
                            }
                            echo "</td>";
                        }
                        echo "</tr>";
                        ?>
                    </tbody>
                </table>
                
                
                <br>
                
                <table class="calendar">
                    <thead>
                    <tr>
                    <th style="background-color: #B5C18E" colspan="7"><strong>JUNE</strong></th>
                    </tr>
                        <tr>
                            <th>Sun</th>
                            <th>Mon</th>
                            <th>Tue</th>
                            <th>Wed</th>
                            <th>Thu</th>
                            <th>Fri</th>
                            <th>Sat</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                        // Generate the calendar starting from May 1st
                        $startDate = strtotime('2023-05-01'); // May 1st, 2023
                        $endDate = strtotime('+90 days', $startDate); // 90 days after May 1st

                        echo "<tr>";
                        for ($i = 0; $i < 42; $i++) {
                            $currentDate = strtotime("+$i days", $startDate);
                            $dayOfWeek = date('D', $currentDate);
                            $dateString = date('M d, Y', $currentDate);

                            // Start a new row every Sunday
                        
            
                            echo "<td";
                            if($i>5 && $i<36)
                            {
                            echo " data-href=\"client_details.php?agent=" . $_SESSION['agent_nr'] . "&index=" . ($counter) . "\"";
                            }
                            echo">";
                            if($i>5 && $i<36)
                            {
                            
                    
                            
                                    echo $counter -31;
                                    $counter++;
                            } 
                            if ($dayOfWeek == 'Sun' && $i != 0 && $i<42) {
                                echo "</tr><tr>";
                            }
                            echo "</td>";
                        }
                        echo "</tr>";
                        ?>
                    </tbody>
                </table>
                
                <br>
                <table class="calendar">
                    <thead>
                    <tr>
                    <th style="background-color: #B5C18E" colspan="7"><strong>JULY</strong></th>
                    </tr>
                        <tr>
                            <th>Sun</th>
                            <th>Mon</th>
                            <th>Tue</th>
                            <th>Wed</th>
                            <th>Thu</th>
                            <th>Fri</th>
                            <th>Sat</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                        // Generate the calendar starting from May 1st
                        $startDate = strtotime('2023-05-01'); // May 1st, 2023
                        $endDate = strtotime('+90 days', $startDate); // 90 days after May 1st

                        echo "<tr>";
                        for ($i = 0; $i < 35; $i++) {
                            $currentDate = strtotime("+$i days", $startDate);
                            $dayOfWeek = date('D', $currentDate);
                            $dateString = date('M d, Y', $currentDate);

                            // Start a new row every Sunday
                        
                
                            echo "<td";
                            if($i>0 && $i<32)
                            {
                            echo " data-href=\"client_details.php?agent=" . $_SESSION['agent_nr'] . "&index=" . ($counter) . "\"";
                            }
                            echo">";
                            if($i>0 && $i<32)
                            {                 
                            
                                    echo $counter -61;
                                    $counter++;
                            } 
                            if ($dayOfWeek == 'Sun' && $i != 0 && $i<31) {
                                echo "</tr><tr>";
                            }
                            echo "</td>";
                        }
                        echo "</tr>";
                        ?>
                    </tbody>
                </table>

            </div>
			
        <?php endif ?>
    </div>
	<script>
document.addEventListener("DOMContentLoaded", () => {
    const cells = document.querySelectorAll("td[data-href]");
    cells.forEach(cell => {
        cell.addEventListener("click", () => {
            window.location.href = cell.dataset.href;
        });
    });
});
</script>
</body>
</html>