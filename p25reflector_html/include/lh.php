<?php
?>
  <div class="panel panel-default">
  <!-- Standard-Panel-Inhalt -->
  <div class="panel-heading">Last Heard List</div>
  <!-- Tabelle -->
  <div class="table-responsive">
  <table id="lh" class="table table-bordered">
  <thead>
    <tr>
      <th>Time (UTC)</th>
      <th>Callsign</th>
      <th>Name</th>
      <th>Id</th>
      <th>Target</th>
      <th>Gateway</th>
      <th>Dur (s)</th>
    </tr>
  </thead>
  <tbody>
<?php
for ($i = 0; $i < count($lastHeard); $i++) {
		$listElem = $lastHeard[$i];
		echo"<tr>";
		echo"<td>$listElem[0]</td>";
		echo"<td><a href='http://www.qrz.com/db/$listElem[1]' target='_blank'>$listElem[1]</a></td>";
		echo"<td>$listElem[2]</td>";
		echo"<td>$listElem[3]</td>";
		echo"<td>$listElem[4]</td>";
		echo"<td>$listElem[5]</td>";
		echo"<td>$listElem[6]</td>";
		echo"</tr>\n";
	}

?>
  </tbody>
  </table>
  </div> 
  <script>
    $(document).ready(function(){
      $('#lh').dataTable();
    });
   </script>
</div>
