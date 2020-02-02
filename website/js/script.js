$(document).ready(function () {
    // Add smooth scrolling to all links in navbar + footer link
    "use strict";

    $(".linkId").click(function () {
        $(this).attr('target', '_blank');
    });


//    $("#cologne").click(function () {
//        if ($("#googleMap").hasClass("hide")) {
//            $("#contactmessage").addClass("hide");
//            $("#googleMap").removeClass("hide");
//            $("#messageSubmit").addClass("hide");
//            initialize();
//        }
//    });

//    $("#contact").click(function () {
//        if ($("#contactmessage").hasClass("hide")) {
//            $("#googleMap").addClass("hide");
//            $("#contactmessage").removeClass("hide");
//            $("#messageSubmit").addClass("hide");
//        }
//    });

    $(".navbar a, footer a[href='#myPage']").on('click', function (event) {
        if (this.hash !== "") {
            event.preventDefault();

            var hash = this.hash;

            $('html, body').animate({
                scrollTop: $(hash).offset().top
            }, 900, function () {

                // Add hash (#) to URL when done scrolling (default click behavior)
                window.location.hash = hash;
            });
        }
    });

    $(window).scroll(function () {
        $(".slideanim").each(function () {
            var pos = $(this).offset().top,
                winTop = $(window).scrollTop();
            if (pos < winTop + 600) {
                $(this).addClass("slide");
            }
        });
    });

    $(function () {
        $('[data-toggle="tooltip"]').tooltip();
    });


//    //Form (not working on GitHubPages)
//    function submitMessage(valid, message) {
//        var messageClasses;
//        if (valid) {
//            messageClasses = "h3 text-center tada animated text-success";
//            $("#contactmessage").addClass("hide");
//        } else {
//            messageClasses = "h3 text-center text-danger";
//        }
//        $("#messageSubmit").removeClass().addClass(messageClasses).text(message);
//    }
//
//    function formSuccess() {
//        $("#contactmessage")[0].reset();
//        submitMessage(true, "Nachricht gesendet!");
//    }
//
//    function submitForm() {
//        // Initiate Variables With Form Content
//        var firstName = $("#firstName").val(),
//            lastName = $("#lastName").val(),
//            email = $("#email").val(),
//            subject = $("#subject").val(),
//            message = $("#message").val();
//
//        $.ajax({
//            type: "POST",
//            url: "php/contact.php",
//            data: "firstName=" + firstName + "&lastName=" + lastName + "&subject=" + subject + "&email=" + email + "&message=" + message,
//            success: function (text) {
//                if (text == "success") {
//                    formSuccess();
//                } else {
//                    submitMessage(false, text);
//                }
//            }
//        });
//    }
//
//    $("#contactmessage").validator().on("submit", function (event) {
//        if (event.isDefaultPrevented()) {
//            // handle the invalid form...
//            submitMessage(false, "Bitte überprüfe deine Eingaben nochmals!");
//        } else {
//            // everything looks good!
//            event.preventDefault();
//            submitForm();
//        }
//    });
//
//
//    $("#contactmessage").submit(function (event) {
//        // cancels the form submission
//        event.preventDefault();
//        submitForm();
//    });


});