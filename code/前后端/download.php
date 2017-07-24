<?php
/**
 * 下载程序接口
 *
 * 进行对Setup.exe资源的下载
 * @author      leyiweb<743285063@qq.com>
 * @version     $Id$
 * @since        1.0
 */
    $file = "Setup.exe";
    header("Content-type: application/octet-stream");
    header('Content-Disposition: attachment; filename="' . basename($file) . '"');
    header("Content-Length: ". filesize($file));
    readfile($file);
?>