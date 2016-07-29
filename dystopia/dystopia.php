<?php
    $xmldoc = new DomDocument();
        $xmldoc->formatOutput = true;

        //store information from form in variables
        $option = $_POST['buchfilm'];
        $titel = $_POST['titel'];
        $titel2 = $_POST['titel'];
        $titel2 = str_replace(' ','',$titel2);
        $bild = $_POST['bild'];
        if($option=="movie")
            {$drehbuch = $_POST['drehbuch'];}
        $autor = $_POST['autor'];
        if($option=="movie")
            {$regie = $_POST['regie'];}
        if($option=="movie")
            {$cast = $_POST['cast'];}
        $jahr = $_POST['jahr'];
        $land = $_POST['land'];
        $inhalt = $_POST['inhalt'];
        $length = $_POST['length'];
        if($option=="movie")
            {$altempf = $_POST['altempf'];}
 
        //get xml file and append tags, elements, attributes
        if ($xml = file_get_contents('dystopia.xml')) {
            $xmldoc->loadXML($xml);

            //finde root element 
            $root = $xmldoc->getElementsByTagName('dystopia')[0];

            //<medien art"">
            $newBM = $xmldoc->createElement('medien');
            $root->appendChild($newBM);
            $artAtt = $xmldoc->createAttribute('art');
            if($option=="book")
                {$artAtt->value = 'buch';}
            elseif($option=="movie")
                {$artAtt->value = 'film';}
            $newBM->appendChild($artAtt);

            //<medium>
            $mediumEl = $xmldoc->createElement('medium');
            $newBM->appendChild($mediumEl);

            //<titel>
            $titelEl = $xmldoc->createElement('titel');
            $mediumEl->appendChild($titelEl);
            $titelTxt = $xmldoc->createTextNode($titel);
            $titelEl->appendChild($titelTxt);

            //<bild src="" id="" alt="" cover="">
            $bildEl = $xmldoc->createElement('bild');
            $mediumEl->appendChild($bildEl);
            $srcAtt = $xmldoc->createAttribute("src");
            $srcAtt->value = $bild;
            $bildEl->appendChild($srcAtt);
            $idAtt = $xmldoc->createAttribute("id");
            $idAtt->value = "cover" . $titel2;
            $bildEl->appendChild($idAtt);
            $altAtt = $xmldoc->createAttribute("alt");
            $altAtt->value = $titel . " cover";
            $bildEl->appendChild($altAtt);
            $coverAtt = $xmldoc->createAttribute("cover");
            $coverAtt->value = "ja";
            $bildEl->appendChild($coverAtt);
            
            //<mitwirkende>
            $mitwirkendeEl = $xmldoc->createElement('mitwirkende');
            $mediumEl->appendChild($mitwirkendeEl);
            
            //<autor drehbuch="" buch"">
            $autorEl = $xmldoc->createElement('autor');
            $mitwirkendeEl->appendChild($autorEl);
            $buchAtt = $xmldoc->createAttribute('buch');
            $buchAtt->value = $autor;
            $autorEl->appendChild($buchAtt);
            if($option=="movie")
                {$drehbuchAtt = $xmldoc->createAttribute('drehbuch');
                $drehbuchAtt->value = $drehbuch;
                $autorEl->appendChild($drehbuchAtt);}
            
            //<regie>
            if($option=="movie")
                {$regieEl = $xmldoc->createElement('regie');
                $mitwirkendeEl->appendChild($regieEl);
                $regieTxt = $xmldoc->createTextNode($regie);
                $regieEl->appendChild($regieTxt);}
            
            //<cast>
            if($option=="movie")
                {$castEl = $xmldoc->createElement('cast');
                $mitwirkendeEl->appendChild($castEl);
                $castTxt = $xmldoc->createTextNode($cast);
                $castEl->appendChild($castTxt);}
            
            //<erscheinungsjahr>
            $jahrEl = $xmldoc->createElement('erscheinungsjahr');
            $mediumEl->appendChild($jahrEl);
            $jahrTxt = $xmldoc->createTextNode($jahr);
            $jahrEl->appendChild($jahrTxt);

            //<land>
            $landEl = $xmldoc->createElement('land');
            $mediumEl->appendChild($landEl);
            $landTxt = $xmldoc->createTextNode($land);
            $landEl->appendChild($landTxt);

            //<inhalt>
            $inhaltEl = $xmldoc->createElement('inhalt');
            $mediumEl->appendChild($inhaltEl);
            $inhaltTxt = $xmldoc->createTextNode($inhalt);
            $inhaltEl->appendChild($inhaltTxt);    

            //<länge>
            $längeEl = $xmldoc->createElement('länge');
            $mediumEl->appendChild($längeEl);
            $längeTxt = $xmldoc->createTextNode($length);
            $längeEl->appendChild($längeTxt);

            //<fsk>
            if($option=="movie")
                {$fskEl = $xmldoc->createElement('fsk');
                $mediumEl->appendChild($fskEl);
                $fskTxt = $xmldoc->createTextNode($altempf);
                $fskEl->appendChild($fskTxt);}
            
            //<verfügbarkeit onlineverfügbar="">
            $verEl = $xmldoc->createElement('verfügbarkeit');
            $mediumEl->appendChild($verEl);
            $onlineAtt = $xmldoc->createAttribute('onlineverfügbar');
            $onlineAtt->value = "nein";
            $verEl->appendChild($onlineAtt);

            //save xml file
            $xmldoc->save('dystopia.xml');

            //inform about save and redirect
            echo ("Gespeichert! Vielen Dank für Ihre Hilfe! <br> Ihre Daten wurden der Mediathek hinzugefügt und sind nun unter der von Ihnen gewählten Kategorie einsehbar. <br> <br> ...redirecting...");
            header( "Refresh:5; url=new.html", true, 303);
            exit;
        }
?>