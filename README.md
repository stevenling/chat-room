<<<<<<< HEAD
=======
聊天室分为四个部分，前端，后端，qt客户端，c++服务器端。

前端：用户注册，应用下载。

后端：登录验证，前端数据传入数据库。

qt客户端：登录界面，聊天界面。

c++服务器端：数据转发。

qt登录界面

>>>>>>> 0e7554fc66eb4825edacebc851c3f4c13f1bd4aa
image

一开始我们没有用户名和密码那么点击注册。跳转到一个网页。

void Login::on_pushButton_2_clicked()//点击 注册 打开一个页面
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://123.207.251.200/register.html")));//yunhu腾讯云注册
}
按钮点击事件，跳转到注册网页。

image
<<<<<<< HEAD

=======
···
>>>>>>> 0e7554fc66eb4825edacebc851c3f4c13f1bd4aa
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>注册账号</title>

    <link rel="stylesheet" href="bootstrap/vendor/bootstrap/css/bootstrap.css"/>
    <link rel="stylesheet" href="bootstrap/dist/css/bootstrapValidator.css"/>

    <script type="text/javascript" src="bootstrap/vendor/jquery/jquery.min.js"></script>
    <script type="text/javascript" src="bootstrap/vendor/bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="bootstrap/dist/js/bootstrapValidator.js"></script>
<body>
<div class="container">
    <div class="row">
        <div class="col-lg-8 col-lg-offset-2">
            <div class="page-header">
                <h2>注册聊天室账号</h2>
            </div>

            <form id="defaultForm" method="post" class="form-horizontal" action="register.php">
                <div class="form-group">
                    <label class="col-lg-3 control-label">用户名</label>
                    <div class="col-lg-5">
                        <input type="text" class="form-control" name="username" />
                    </div>
                </div>

                <div class="form-group">
                    <label class="col-lg-3 control-label">密码</label>
                    <div class="col-lg-5">
                        <input type="password" class="form-control" name="password" />
                    </div>
                </div>

                <div class="form-group">
                    <label class="col-lg-3 control-label">再次输入密码</label>
                    <div class="col-lg-5">
                        <input type="password" class="form-control" name="repassword" />
                    </div>
                </div>

                <div class="form-group">
                    <div class="col-lg-9 col-lg-offset-3">
                        <button type="submit" class="btn btn-primary">提交注册</button>
                    </div>
                </div>
            </form>
        </div>
    </div>
</div>
<<<<<<< HEAD

=======
···
>>>>>>> 0e7554fc66eb4825edacebc851c3f4c13f1bd4aa
<script type="text/javascript">
    $(document).ready(function() {
        $('#defaultForm')
            .bootstrapValidator({
                message: 'This value is not valid',
                feedbackIcons: {
                    valid: 'glyphicon glyphicon-ok',
                    invalid: 'glyphicon glyphicon-remove',
                    validating: 'glyphicon glyphicon-refresh'
                },
                fields: {
                    username: {
                        message: 'The username is not valid',
                        validators: {
                            notEmpty: {
                                message: '用户名不能为空'
                            },
                            stringLength: {
                                min: 6,
                                max: 30,
                                message: '用户名至少6个字符，至多30字符'
                            },
                            /*remote: {
                             url: 'remote.php',
                             message: 'The username is not available'
                             },*/
                            regexp: {
                                regexp: /^[a-zA-Z0-9_\.]+$/,
                                message: '用户名只能由字母、数字、点和下划线组成'
                            }
                        }
                    },
                    password: {
                        validators: {
                            notEmpty: {
                                message: '密码不能为空'
                            },
                            stringLength: {
                                min: 8,
                                message: '密码最少8位以上'
                            },
                            regexp: {
                                regexp: /^[a-zA-Z0-9_\.]+$/,
                                message: '密码只能由字母、数字、点和下划线组成'
                            }
                        }
                    },
                    repassword: {
                        validators: {
                            notEmpty: {
                                message: '请再次输入密码'
                            },
                            identical:{
                                field:'password',
                                message:'两次密码输入不一致'
                            }
                        }
                    }
                }
            })
           .on('success.form.bv', function(e) {
                // Prevent form submission
                e.preventDefault();

                // Get the form instance
                var $form = $(e.target);

                // Get the BootstrapValidator instance
                var bv = $form.data('bootstrapValidator');

                // Use Ajax to submit form data
                $.post($form.attr('action'), $form.serialize(), function(result) {
                    str = eval(result);
                    if(str["result"] == "true") {
                        alert("账号注册成功！")
                    }
                    else {
                        alert("账号已经存在，请重试！")
                    }
                    console.log(result);
                }, 'json');
            });
    });
</script>
</body>
<<<<<<< HEAD
</html>
=======
</html>···
>>>>>>> 0e7554fc66eb4825edacebc851c3f4c13f1bd4aa
