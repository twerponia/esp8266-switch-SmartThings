
       
$(document).ready(function () {

    $("#boff").click(function () {
        $.getJSON("/switch-api", { name: "off" }, function (result) {
            $.each(result, function () {
                $('#text1').text(this.state);   
            });
        });
    });

    $("#bon").click(function () {
        $.getJSON("/switch-api", { name: "on" }, function (result) {
            $.each(result, function () {
                $('#text1').text(this.state);
            });
        });
    });



});