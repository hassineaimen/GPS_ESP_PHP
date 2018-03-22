<?php
  //dir = $_POST["dir"];

  $dir1 = isset($_POST['dir1']) ? $_POST['dir1'] : NULL;
  $dir2 = isset($_POST['dir2']) ? $_POST['dir2'] : NULL;
  echo file_get_contents($dir1);
  echo file_get_contents($dir2);
  $file1 =  './test1.txt';
  $file2 =  './test2.txt';
  file_put_contents($file1, $dir1);
  file_put_contents($file2, $dir2);
  

  
?>