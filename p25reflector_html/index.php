<?php
$time = microtime();
$time = explode(' ', $time);
$time = $time[1] + $time[0];
$start = $time;
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Sat, 26 Jul 1997 05:00:00 GMT");
// do not touch this includes!!! Never ever!!!
include "config/config.php";
include "include/tools.php";
include "include/functions.php";
include "include/init.php";
include "version.php";
?>





<!DOCTYPE html>
<html lang="en">
<head>
  <title>P25 TG007 SOMEWHERE</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="<?php echo REFRESHAFTER?>">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2/dist/js/bootstrap.bundle.min.js"></script>

  <!-- Favicon -->
  <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png">
  <link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png">
  <link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png">
  <link rel="manifest" href="/site.webmanifest">
  <link rel="mask-icon" href="/safari-pinned-tab.svg" color="#5bbad5">

</head>
<body>
  
<div class="container pt-5">

  <div class="row">
    <div class="col-sm-3 text-center">
      <img src="P25Logo.jpg" class="img-thumbnail" width="200" alt="P25 Logo">

   </div>
    <div class="col-sm-6 text-center">
     <p class="h2 bg-danger">Dashboard P25</p>
     <p class="h2">TG Number  </p>
     <p class="h2 bg-danger">hosted on SERVER </p>
   </div>
    <div class="col-sm-3" >
      <img src="OE9_p25.jpg" class="img-circle" width="200" alt="P25 Logo">

   </div>
  </div>

<div class="m-4">
    <div class="card text-center">
        <div class="card-header">
            <ul class="nav nav-pills card-header-pills">
                <li class="nav-item">
                    <a href="#lastheard" class="nav-link active" data-bs-toggle="tab">Last Heard</a>
                </li>
                <li class="nav-item">
                    <a href="#gateways" class="nav-link" data-bs-toggle="tab">Connected Gateways</a>
                </li>
                <li class="nav-item">
                    <a href="#tgs" class="nav-link" data-bs-toggle="tab">other P25 Talkgroups</a>
                </li>
            </ul>
        </div>
        <div class="card-body">
            <div class="tab-content">
                <div class="tab-pane fade show active" id="lastheard">
                    <h5 class="card-title">last heard</h5>
                    <p class="card-text">

                       <?php checkSetup(); include "include/lh.php"; ?>
                    </p>
                </div>
                <div class="tab-pane fade" id="gateways">
                    <h5 class="card-title">connected gateways</h5>
                    <p class="card-text">

                      <?php include "include/gateways.php"; ?>
                    </p>
                </div>
                <div class="tab-pane fade" id="tgs">
                    <h5 class="card-title">P25 other TGs</h5>
                    <div class="row">    <a href="http://xlx-hc.ham-digital.org/P25Reflector-Dashboard/" target="_blank">TG 10320/10310 Germany</a> </div>
                    <div class="row"><a href="https://p25-eu.n18.de/" target="_blank">TG 10300 Europe</a></div>
                    <div class="row"><a href="http://p25.projekt-pegasus.net/" target="_blank">TG 10328 Pegasus Project</a></div>
                    <div class="row"><a href="http://dl1bh.ddns.net:4446/" target="_blank">TG 10945 Interlink XLX945P</a></div>
            </div>
        </div>
    </div>
</div>



<div class="row">
<div class="col text-center" >
<?php
$lastReload = new DateTime();
echo "Last Reload ".$lastReload->format('Y-m-d, H:i:s');

?>
</div>
<div class="col text-center">
<p>Dashboard based on YSF Dashboard from DG9VH <a href="https://github.com/dg9vh/YSFReflector-Dashboard">https://github.com/dg9vh/YSFReflector-Dashboard</a> | New Webdesign 08/2022 by DD7RG</p>
</div>
</div>


</div>
</body>
</html>

