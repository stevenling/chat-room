<?php
/**
 * 注册用户信息接口
 *
 * 前台通过post传入username和password
 * 去空处理
 * 查询数据库，如果存在username，返回false
 * 如果不存在username,插入当前user信息，返回true
 * 返回格式为json
 * @author      leyiweb<743285063@qq.com>
 * @version     $Id$
 * @since        1.0
 */

    /*$serverName = "127.0.0.1";
    $username = "root";
    $password = "asd123";
    $dataBase = "Raspberry";*/
	$serverName = "127.0.0.1";
    $username = "root";
    $password = "ViMxGaVxALFb";
    $dataBase = "yunhu";

    $conn = new mysqli($serverName, $username, $password,$dataBase);

    if($conn->connect_error) {
        echo "error";
        echo "<br>";
    }

    $sql = "SET NAMES UTF8";
    if($conn->query($sql) === true) {
        //echo "set success<br>";
    }
    else {
       echo "set fail<br>";
    }

    $username = $_POST['username'];
    $password = $_POST['password'];
    $result = array();

    if($username == "") {
        $result["result"] = "false";
    }
    else {
        $add = $conn->prepare("INSERT INTO userInformation(username,password)  VALUES(?,?)");
        $add->bind_param("ss", $username,$password);

        $stmt = $conn->prepare("SELECT * FROM userInformation WHERE username=?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->store_result();
        $stmt->bind_result($id);


        if($stmt->fetch()) {
            $result["result"] = "false";
        }
        else {
            $add->execute();
            $result["result"] = "true";
        }
    }

    echo json_encode($result);

?>