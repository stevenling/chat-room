<?php
/**
 * 树莓派验证用户信息接口
 *
 * 树莓派通过post传入username和password
 * 如果数据库中匹配正确，返回true
 * 如果数据库中匹配到，但密码错误，返回error0
 * 如果数据库中匹配不到，返回error1
 * 返回格式为json
 * @author      leyiweb<743285063@qq.com>
 * @version     $Id$
 * @since        1.0
 */

    $serverName = "127.0.0.1";
    $username = "root";
    $password = "123456";
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

    $username_post = $_POST['username'];
    $password_post = $_POST['password'];
    $result = array();

    $stmt = $conn->prepare("SELECT username,password FROM userInformation WHERE username=?");
    $stmt->bind_param("s", $username_post);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($username_db,$password_db);

    if($stmt->fetch()) {
        if(($username_db == $username_post) && ($password_db == $password_post)) {
            $result["result"] = "true";
        }
        else {
            $result["result"] = "error0";
        }
    }
    else {
            $result["result"] = "error1";
    }
    echo $result["result"];


?>