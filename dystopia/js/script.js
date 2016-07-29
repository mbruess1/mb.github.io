/*Proseminar HKI - BSI I, Melanie Brüssel, 6068626, 15.03.2015*/

$(document).ready(function () {
    "use strict";
    //delete all div & css created from other js calls
    function makeready() {
        $("#home a").css("color", "#555");
        $("#filme a").css("color", "#555");
        $("#merkliste a").css("color", "#555");
        $("#books a").css("color", "#555");
        $("#new a").css("color", "#555");
        $("#info").remove();
        $("#slide1").remove();
        $("#slide3").remove();
        $("body").animate({ scrollTop: 0 }, "fast");
    }
    //global variables 
    var arr = [],
        i;

//HOME 
    if (/home/.test(self.location.href)) {
        //make ready
        makeready();
        $("#home a").css("color", "orange");
        $("#slide2").append('<img id="down" src="img/arrow%20down.png" alt="arrow-down"/>');
        //append slide3 and fill with content
        $("#content").append("<div id='slide3'/>");
        $("#slide3").append("<h2>DISTOPIA</h2>" + "<p>Wilkommen in der Zukunft!</p>" + "<p>Wir schreiben das Jahr X; &quot;Utopia&quot; hat versagt und &quot;Distopia&quot; heißt das Konzept welches die Gesellschaft regiert. Die zuerst unbedentklch scheinenendne Entwicklungen der Vergangenheit, die nur von wenigen als bedenklich eingestuft und kritisiert wurnden, haben in den letzten Jarhen ihren Höhepunkt erlang und unsere Welt zu dem düsteren, entzeitlichen Ort gemacht den wier Distopia nennen. Viele unserer Mitbürger sind auf diese Misszustände jedoch immrnoch nicht aufemrksam geworden.</p>" + "<p>Diese Sammlung enthält Werken, die frühzeitig darauf hinwiesen wie die Zukunft der Menschen aussehen könnte.</p>");
    }
    
 //FILME
    if (/movies/.test(self.location.href)) {
        //make ready
        makeready();
        $("#filme a").css("color", "orange");
        $("#slide2").before("<div id='slide1'/>");

        //LOAD CONTENT 
        $.ajax({
            url: './dystopia.xml',
            xmldataType: 'xml',
            success: function (xmldata) {
                /*console.log(xmldata);*/

                $(xmldata).find("medien[art='film']").each(function () {
                    var titel = $(this).find('titel').text(),
                        jahr = $(this).find('erscheinungsjahr').text(),
                        //cover
                        myImage = $('<img/>'),
                        src = $(this).find("bild").attr("src"),
                        alt = $(this).find("bild").attr("alt"),
                        id = $(this).find("bild").attr("id");
                    myImage.attr('src', src);
                    myImage.attr('alt', alt);
                    myImage.attr('id', id);
                    myImage.attr("class", "cover");
                    myImage.attr("title", titel  + " (" + jahr + ")");
                    
                    //append image
                    $("#slide1").append(myImage);
                });
            },
            error: function () {
                $("#slide2").before("<div id='slide1'/>");
                $("#slide1").text("Es ist ein Fehler aufgetreten");
            }
        });

        //LOAD DETAILS
        $(document).on("click", ".cover", function more() {
            var clicked = this.id,
                position = $("body").scrollTop();

            if ($("#info")) {
                $("#info").remove();
            }
            
            //scroll to top
            $("body").animate({ scrollTop: 0 }, "fast");

            $.ajax({
                url: './dystopia.xml',
                xmldataType: 'xml',
                success: function xmldetail(xmldata) {
                    $(xmldata).find("bild[id=" + clicked + "]").each(function () {
                        var daten = $(xmldata).find("bild[id=" + clicked + "]").parentsUntil("medien[art]"),
                            titel = $(daten).find('titel').text(),
                            TITEL = titel.toLocaleUpperCase(),
                            jahr = $(daten).find('erscheinungsjahr').text(),
                            fsk = $(daten).find('fsk').text(),
                            //trailer
                            trailer = $(daten).find('trailer').text(),
                            myiframe = $('<iframe/>'),
                            src = $(daten).find("trailer").attr("src"),
                            id = $(daten).find("trailer").attr("id"),
                            name = $(daten).find("trailer").attr("name"),
                            
                            cast = $(daten).find('cast').text(),
                            regie = $(daten).find('regie').text(),
                            drehbuch = $(daten).find("autor").attr("drehbuch"),
                            based = $(daten).find("autor").attr("buch"),
                            inhalt = $(daten).find('inhalt').text(),
                            ondemand = $(daten).find('verfügbarkeit').text(),
                            length = $(daten).find('länge').text(),
                            land = $(daten).find('land').text();

                        myiframe.attr('src', src);
                        myiframe.attr('id', id);
                        myiframe.attr("name", name);
                        myiframe.attr("height", "315");
                        myiframe.attr("width", "590");
                        myiframe.attr("frameborder", "0");
                        myiframe.attr("class", "video");
                        myiframe.attr("allowfullscreen", "0");
                        
                        //create and fill #info
                        $("body").append("<div id='info'>");
                        $("#info").append('<img class="close" src="./img/close.png" alt="schließen" titel="schließen"/>' + "<div id='heading'> <h2>" + TITEL + " (" + jahr + ")" + "</h2> </div>" + "<div id='links'>" + "<ul>" + "<li>" +  "<div id='long'> <h3>Länge: </h3>" + length + "</div> </li>" + "<li>" + "<div id='age'> <h3>Altersfreigabe: </h3>" + fsk + "</div> </li>" + "</ul>" + "<hr>" + "<ul>" + "<li>" + "<div id='country'> <h3>Produktionsland: </h3>" + land + "</div> </li>" + "<li>" + "<div id='screenplay'> <h3>Drehbuch: </h3>" + drehbuch + "</div> </li>" + "<li id='basedon'>" + "<div id='bookcopy'> <h3>Vorlage von: </h3>" + based + "</div></li>" + "<li>" + "<div id='direct'> <h3>Regie: </h3>" + regie + "</div></li>" + "<li>" + "<div id='schauspielcast'> <h3>Cast: </h3>" + cast + "</div> </li>" + "</ul>" + "</div>" + "<div id='rechts'>" + "<div id='inh'> <h3>Inhaltsangabe: </h3>" + inhalt + "</div> <br>" + "<br>" + "<div id='vid' class='videowrap'/>" + "</div>" + "<div id='unten'/>" + "<hr>" + '<div>' + "<ul id='ondemand'/>" + "</div>");
                        $(".videowrap").append(myiframe);

                        $("li:contains('undefined')").remove();
                        
                        $(daten).find("online").each(function (i) {
                            var online = $(daten).find("online").eq(i).text(),
                                quelle = $(daten).find("online").eq(i).attr("quelle");

                            $("#ondemand").append("<li>" + "<a class='demand'>" + online + "</a>" + "</li>");
                            $(".demand").eq(i).attr("href", quelle);
                        });

                        //close #info and return to lastpositon in media library
                        $(document).on("click", ".close", function () {
                            $("#info").remove();
                            $("body").animate({ scrollTop: position }, "fast");
                            position = $("body").scrollTop(0);
                        });
                    });
                },
                error: function () {
                    $("#slide1").text("Es ist ein Fehler aufgetreten");
                }
            });
        });
    }
      
//Bücher
    if (/books/.test(self.location.href)) {
        //make ready
        makeready();
        $("#books a").css("color", "orange");
        $("#slide2").before("<div id='slide1'/>");

       //LOAD CONTENT
        $.ajax({
            url: './dystopia.xml',
            xmldataType: 'xml',
            success: function (xmldata) {
                $(xmldata).find("medien[art='buch']").each(function () {
                    var titel = $(this).find('titel').text(),
                        jahr = $(this).find('erscheinungsjahr').text(),
                        //cover
                        myImage = $('<img/>'),
                        src = $(this).find("bild").attr("src"),
                        alt = $(this).find("bild").attr("alt"),
                        id = $(this).find("bild").attr("id");
                    myImage.attr('src', src);
                    myImage.attr('alt', alt);
                    myImage.attr('id', id);
                    myImage.attr("class", "cover");
                    myImage.attr("title", titel  + " (" + jahr + ")");
                    
                    //append images
                    $("#slide1").append(myImage);
                });
            },
            error: function () {
                $("#slide2").before("<div id='slide1'/>");
                $("#slide1").text("Es ist ein Fehler aufgetreten");
            }
        });

        //LOAD DETAILS
        $(document).on("click", ".cover", function more() {
            var clicked = this.id,
                position = $("body").scrollTop();
            
            //make ready
            if ($("#info")) {
                $("#info").remove();
            }
            //scroll to top
            $("body").animate({ scrollTop: 0 }, "fast");

            $.ajax({
                url: './dystopia.xml',
                xmldataType: 'xml',
                success: function xmldetail(xmldata) {
                    $(xmldata).find("bild[id=" + clicked + "]").each(function () {
                        var daten = $(xmldata).find("bild[id=" + clicked + "]").parentsUntil("medien[art ='buch']"),
                            titel = $(daten).find('titel').text(),
                            TITEL = titel.toLocaleUpperCase(),
                            jahr = $(daten).find('erscheinungsjahr').text(),
                            fsk = $(daten).find('fsk').text(),
                            //trailer
                            trailer = $(daten).find('trailer').text(),
                            myiframe = $('<iframe/>'),
                            src = $(daten).find("trailer").attr("src"),
                            id = $(daten).find("trailer").attr("id"),
                            name = $(daten).find("trailer").attr("name"),
                            
                            cast = $(daten).find('cast').text(),
                            regie = $(daten).find('regie').text(),
                            drehbuch = $(daten).find("autor").attr("drehbuch"),
                            based = $(daten).find("autor").attr("buch"),
                            inhalt = $(daten).find('inhalt').text(),
                            ondemand = $(daten).find('verfügbarkeit').text(),
                            length = $(daten).find('länge').text(),
                            land = $(daten).find('land').text();

                        myiframe.attr('src', src);
                        myiframe.attr('id', id);
                        myiframe.attr("name", name);
                        myiframe.attr("height", "315");
                        myiframe.attr("width", "590");
                        myiframe.attr("frameborder", "0");
                        myiframe.attr("class", "video");
                        myiframe.attr("allowfullscreen", "0");
                        
                        //create and fill #info
                        $("body").append("<div id='info'>");
                        $("#info").append('<img class="close" src="./img/close.png" alt="schließen" titel="schließen"/>' + "<h2>" + TITEL + " (" + jahr + ")" + "</h2>" + "<div id='links'>" + "<ul>" + "<li>" +  "<h3>Seitenanzahlen: </h3>" + length + "</li>" + "</ul>" + "<hr>" + "<ul>" + "<li id='basedon'>" + "<h3>Autor: </h3>" + based + "</li>" + "<li>" + "<h3>Land der Veröffentlichung: </h3>" + land + "</li>" + "</ul>" + "</div>" + "<div id='rechts'>" + "<h3>Inhaltsangabe: </h3>" + inhalt + "</div>");

                        $("li:contains('undefined')").remove();

                        //close #info and return to lastpositon in media library
                        $(document).on("click", ".close", function () {
                            $("#info").remove();
                            $("body").animate({ scrollTop: position }, "fast");
                            position = $("body").scrollTop(0);
                        });
                    });
                },
                error: function () {
                    $("#slide1").text("Es ist ein Fehler aufgetreten");
                }
            });
        });
    }
 
//HINZUFÜGEN
    if (/new/.test(self.location.href)) {
        //make ready
        makeready();
        $("#new a").css("color", "orange");
        $("#slide2").before("<div id='slide1'/>");
        
        //create select for form #bmform
        $("#slide1").append('<div id="anweisung"> <h4>Hier können sie neue Bücher und Filme eintragen und somit helfen diese Mediathek zu erweitern</h4> </div> <select form="bmform" id="buchfilm" name="buchfilm" required> <option value="">Bitte wählen Sie</option> <option value="book">Buch</option> <option value="movie">Film</option> </select>');
        
        //create specific form #bmform everytime select is chosen
        $('#buchfilm').change(function () {
            $("#buchform").remove();
            $("#movieform").remove();
            //selected book
            if ($("#buchfilm").val() === "book") {
                $("#buchfilm").after('<div class="form"> <form id="bmform"  action="dystopia.php" method="post"> <fieldset> <div id="buchform"> <label for="titel">Titel*:</label> <input type="text" name="titel" id="titel" class="form" placeholder="Buchtitel" required> <br> <br> <label for="bild">Cover*:</label> <input type="url" name="bild" id="bild" class="form" placeholder="http://buchcover.jpg" required> <br> <br> <label for="autor">Autor/in*:</label> <input type="text" name="autor" id="autor" class="form" placeholder="Autor/in" required> <br> <br> <label for="jahr">Erscheinungsjahr*:</label> <input type="number" name="jahr" id="jahr" class="form" min="1000" max="2050" placeholder="JJJJ" required> <br> <br> <label for="land">Land der Veröffentlichung*:</label> <input type ="text" name="land" id="land" class="form" placeholder="Land" required> <br> <br> <label for="length">Seitenanzahl*:</label> <input type ="number" name="length" id="length" class="form" min="1" placeholder="Anzahl der Seiten" required> <br> <br> <div class="txtarea"> <label for="inhalt">Inhaltsangabe*:</label> </div> <textarea name="inhalt" id="inhalt" rows="10" cols="50" class="form" placeholder="Zusammenfassung des Buches" required></textarea> <br> <br> <div id="send"> <input type="submit" value="Hinzufügen" class="submit"> </div> </div> </fieldset> </form> </div> </div>');
            //selected movie
            } else if ($("#buchfilm").val() === "movie") {
                $("#buchfilm").after('<div class="form"> <form id="bmform"  action="dystopia.php" method="post"> <fieldset> <div id="movieform"> <label for="titel">Titel*:</label> <input type="text" name="titel" id="titel" class="form" placeholder="Buchtitel" required> <br> <br> <label for="bild">Filmplakat*:</label> <input type="url" name="bild" id="bild" class="form" placeholder="http://filmplakat.jpg" required> <br> <br> <label for="drehbuch">Drehbuch:*</label> <input type="text" name="drehbuch" id="drehbuch" class="form" placeholder="Autor/in" required> <br> <br> <label for="autor">Buchvorlage von:</label> <input type="text" name="autor" id="autor" class="form" placeholder="Autor/in" required> <br> <br> <label for="regie">Regiseur/in:*</label> <input type="text" name="regie" id="regie" class="form" placeholder="Regiseur/in" required> <br> <br> <div class="txtarea"> <label for="cast">Schauspieler:*</label> </div> <textarea name="cast" id="cast" rows="10" cols="50" class="form" placeholder="Schauspieler" required></textarea> <br> <br> <label for="jahr">Erscheinungsjahr*:</label> <input type="number" name="jahr" id="jahr" class="form" min="1000" max="2050" placeholder="JJJJ" required> <br> <br> <label for="land">Produktionsland*:</label> <input type ="text" name="land" id="land" class="form" placeholder="Land" required> <br> <br> <label for="length">Länge*:</label> <input type ="number" name="length" id="length" class="form" min="1" placeholder="Länge" required> <br> <br> <label for="altempf">FSK:</label> <input type ="number" name="altempf" id="altempf" class="form" max="150" placeholder="FSK"> <br> <br> <div class="txtarea"> <label for="inhalt">Inhaltsangabe*:</label> </div> <textarea name="inhalt" id="inhalt" rows="10" cols="50" class="form" placeholder="Zusammenfassung des Buches" required></textarea> <br> <br> <div id="send"> <input type="submit" value="Hinzufügen" class="submit"> </div> </div> </fieldset> </form> </div>');
            }
        });
    }

//SLIDESHOW
    //Load Images and push in arary
    $.ajax({
        url: './dystopia.xml',
        xmldataType: 'xml',
        success: function xmldetail(xmldata) {
            $(xmldata).find("bild[cover='nein']").parent().each(function () {
                var imgsrc = $(this).find("bild[cover='nein']").attr("src");
                arr.push(imgsrc);
                i = 0;
                $('#slide2').css('background-image', 'url(' + arr[i] + ')');
                return i;
            });
        },
        error: function () {
            $("#slide2").text("Bild konnte nicht geladen werden");
        }
    });

//Arrows
    //click left (move backwards through arr)
    $(document).on("click", "#left", function () {
        if (i > arr.length - 1) {
            i = 0;
        } else if (i < arr.length - arr.length + 1) {
            i = arr.length;
        }
        $('#slide2').css('background-image', 'url(' + arr[i - 1] + ')');
        i--;
        return i;
    });

    //click right (move forward through arr)
    $(document).on("click", "#right", function () {
        if (i >= arr.length - 1) {
            i = -1;
        }
        $('#slide2').css('background-image', 'url(' + arr[i + 1] + ')');
        i++;
        return i;
    });
    
    //click down
    $(document).on("click", "#down", function () {
        $('body').animate({
            scrollTop: $("#slide3").offset().top
        }, "fast");

    });
});
    