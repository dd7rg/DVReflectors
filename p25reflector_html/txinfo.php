<?php
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Sat, 26 Jul 1997 05:00:00 GMT");
include "config/config.php";
include "include/tools.php";
include "include/functions.php";
$configs = getP25ReflectorConfig();
$logLines = getShortP25ReflectorLog();
$reverseLogLines = $logLines;
array_multisort($reverseLogLines,SORT_DESC);
$lastHeard = getLastHeard($reverseLogLines, True);
if(isset($lastHeard[0])){
	$listElem = $lastHeard[0];
	if (strlen($listElem[0]) !== 0) {
		echo "<tr>";
		echo"<td nowrap>$listElem[0]</td>";
		if (constant("SHOWQRZ") && $listElem[1] !== "??????????" && !is_numeric($listElem[1])) {
			echo"<td nowrap><a target=\"_new\" href=\"https://qrz.com/db/$listElem[1]\">".str_replace("0","&Oslash;",$listElem[1])."</a></td>";
		} else {
			echo"<td nowrap>".str_replace("0","&Oslash;",$listElem[1])."</td>";
		}
		echo"<td nowrap>$listElem[2]</td>";
		echo"<td nowrap>$listElem[3]</td>";
		$UTC = new DateTimeZone("UTC");
		$d1 = new DateTime($listElem[0], $UTC);
		$d2 = new DateTime('now', $UTC);
		$diff = $d2->getTimestamp() - $d1->getTimestamp();
		echo"<td nowrap>$diff s</td>";
		echo "</tr>";
	}
}
?>
