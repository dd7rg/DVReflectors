<?php
//Some basic inits
$configs = getP25ReflectorConfig();
$logLines = getP25ReflectorLog();

$reverseLogLines = $logLines;
array_multisort($reverseLogLines,SORT_DESC);
$lastHeard = getLastHeard($reverseLogLines);
$allHeard = getHeardList($reverseLogLines);
?>