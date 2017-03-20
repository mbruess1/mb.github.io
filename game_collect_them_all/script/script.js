//variables
var renderer, scene, camera;
var geometry, material, mesh;
var ambientLight, hemisphereLight, shadowLight;

var score = 0;
var end = false;
var playing = false;
var timeoutId;

var world;
var meshes = [],
    bodies = [],
    trashT = [],
    trashC = [];

var playerMesh;
var playerBody;

var moveLeft = false;
var moveRight = false;

var cannonDebugRenderer;

var addInputListeners = function () {
    document.addEventListener('keydown', onKeyDown, false);
    document.addEventListener('keyup', onKeyUp, false);
    document.addEventListener('touchend', onTouchEnd, false);
    document.addEventListener('touchmove', onTouchMove, false);
}
var removeInputListeners = function () {
    document.removeEventListener('keydown', onKeyDown, false);
    document.removeEventListener('keyup', onKeyUp, false);
    document.removeEventListener('touchmove', onTouchMove, false);
    document.removeEventListener('touchend', onTouchEnd, false);
}

var resetGame = function () {
    score = 0;
    end = false;
    playing = false;

    document.getElementById("infos").innerHTML = "";
    window.clearTimeout(timeoutId);
    addInputListeners();
}

var endGame = function (message) {
    moveLeft = false;
    moveRight = false;
    removeInputListeners();
    end = true;
    playing = false;
    console.log(message);
    document.getElementById("infos").innerHTML = message;
}

//resize
var windowResize = function () {
    renderer.setSize(window.innerWidth, window.innerHeight);
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
};

// lights
var light = function () {
    hemisphereLight = new THREE.HemisphereLight(0xaaaaaa, 0x000000, 0.9);

    ambientLight = new THREE.AmbientLight(0xdc8874, 0.5);

    shadowLight = new THREE.DirectionalLight(0xffffff, 0.9);
    shadowLight.position.set(150, 350, 350);
    shadowLight.castShadow = true;
    shadowLight.shadow.camera.left = -400;
    shadowLight.shadow.camera.right = 400;
    shadowLight.shadow.camera.top = 400;
    shadowLight.shadow.camera.bottom = -400;
    shadowLight.shadow.camera.near = 1;
    shadowLight.shadow.camera.far = 1000;
    shadowLight.shadow.mapSize.width = 4096;
    shadowLight.shadow.mapSize.height = 4096;

    scene.add(hemisphereLight);
    scene.add(shadowLight);
    scene.add(ambientLight);
};

var player = function () {
    //THREE
    geometry = new THREE.BoxGeometry(3, 3, 3);

    var i;
    for (i = 0; i < geometry.faces.length; i++) {
        var face = geometry.faces[i];
        face.color.setHex(Math.random() * 0xffffff);

    }
    material = new THREE.MeshLambertMaterial({
        color: Math.random() * 0xffffff
    });

    playerMesh = new THREE.Mesh(geometry, material);

    scene.add(playerMesh);

    //CANNON
    var boxShape = new CANNON.Box(new CANNON.Vec3(1.5, 1.5, 1.5)); //body combines shape and material (bouncy, ...)
    var boxMaterial = new CANNON.Material();
    playerBody = new CANNON.Body({
        mass: 0.5,
        shape: boxShape,
        material: boxMaterial
    });

    playerBody.position.y = 1.2;

    world.add(playerBody);
    playerMesh.position.copy(playerBody.position);

    playerBody.addEventListener("collide", function playerCollision(e) {
        for (i = 0; i < bodies.length; i++) {
            if (e.body.id === bodies[i].id) {
                console.log("MESH " + i + " with ID " + e.body.id + " got hit.");
                trashT.push(meshes[i]);
                trashC.push(bodies[i]);
            }
        }
    });
};

var ball = function (x, y, z) {
    //THREE
    geometry = new THREE.SphereGeometry(1);

    var i;
    for (i = 0; i < geometry.faces.length; i++) {
        var face = geometry.faces[i];
        face.color.setHex(Math.random() * 0xffffff);

    }
    material = new THREE.MeshLambertMaterial({
        color: Math.random() * 0xffffff,
        opacity: 0.5,
        transparent: true,
    });

    var mesh = new THREE.Mesh(geometry, material);

    scene.add(mesh);
    meshes.push(mesh);

    //CANNON
    var sphereShape = new CANNON.Sphere(1); //body combines shape and material (bouncy, ...)
    var sphereMaterial = new CANNON.Material();
    var sphereBody = new CANNON.Body({
        mass: 0,
        shape: sphereShape,
        material: sphereMaterial
    });
    sphereBody.position.set(x, y, z);

    world.add(sphereBody);
    sphereBody.collisionResponse = 0;
    bodies.push(sphereBody);

    sphereBody.addEventListener("collide", function ballCollision(e) {
        if (end !== true && playing === true) {
            score += 1;
            console.log("score= " + score);
        }
    });
};

var addBalls = function () {
    var i;
    //remove
    for (i = 0; i < meshes.length; i++) {
        scene.remove(bodies[i]);
        world.remove(meshes[i]);
    }

    //add
    for (i = 0; i < 1000; i++) {
        ball(
            0,
            Math.random() * 400,
            Math.random() * 200 - 100
        );
    }
}

var ground = function () {
    //THREE
    var groundGeometry = new THREE.PlaneGeometry(20, 200, 10, 10);
    var groundMaterial = new THREE.MeshLambertMaterial({
        color: 0x444444,
        side: THREE.DoubleSide
    });
    var ground = new THREE.Mesh(groundGeometry, groundMaterial);
    ground.position.y = -0.5;
    ground.rotation.x = Math.PI / 2.0;
    scene.add(ground);

    //CANNON
    var groundShape = new CANNON.Plane();
    groundMaterial = new CANNON.Material({
        color: 0xfffffff
    });
    var groundBody = new CANNON.Body({
        mass: 0,
        shape: groundShape,
        material: groundMaterial,
        id: 99999
    });
    groundBody.quaternion.setFromAxisAngle(new CANNON.Vec3(1, 0, 0), -Math.PI / 2); //rotate ground to not look to camera 

    world.add(groundBody);
    ground.position.copy(groundBody.position);
};


var init = function () {
    resetGame();

    //renderer
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(0xff0000, 0.5);
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);

    //scene
    scene = new THREE.Scene();

    //camera
    camera = new THREE.PerspectiveCamera(20, window.innerWidth / window.innerHeight, 1, 1000);
    camera.position.set(90, 2, 0);
    camera.lookAt(new THREE.Vector3(0, 80, 0));

    //world
    world = new CANNON.World();
    world.broadphase = new CANNON.NaiveBroadphase();
    world.gravity.set(0, -15, 0);

    //populate
    light();
    ground();

    player();
    addBalls();

    //event-listener
    window.addEventListener('resize', windowResize, false);
    addInputListeners();

    //debug
    cannonDebugRenderer = new THREE.CannonDebugRenderer(scene, world);

    update();
};

//user input
function onKeyDown(event) {
    playing = true;
    switch (event.keyCode) {
        case 37: // left
        case 65: // a
            moveLeft = true;
            break;
        case 39: // right
        case 68: // d
            moveRight = true;
            break;
        default:
            break;
    }
    return false;
}

function onTouchMove(event) {
    event.preventDefault();
    playing = true;
    for (var i = 0; i < event.touches.length; i++) {
        var touche = event.touches[i];

        if (touche.clientX < screen.width / 2) { //left
            moveRight = false;
            moveLeft = true;
        } else if (touche.clientX > screen.width / 2) { //right
            moveLeft = false;
            moveRight = true;
        }
    }
    return false;
}

function onKeyUp(event) {
    playing = true;
    switch (event.keyCode) {
        case 37: // left
        case 65: // a
            moveLeft = false;
            break;
        case 39: // right
        case 68: // d
            moveRight = false;
            break;
        default:
            break;
    }
    return false;
}

function onTouchEnd(event) {
    playing = true;

    moveLeft = false;
    moveRight = false;

    return false;
}

var update = function () {
    requestAnimationFrame(update);

    //WIN
    if (playerBody.position.y > 390) {
        endGame("YOU WON!");
    }
    //GAME OVER
    (function checkGameOver() {
        var checkScore = score;
        timeoutId = setTimeout(function timeout() {
            if (checkScore === score && score > 0 && playing === true) {
                endGame("GAME OVER.");
            } else {
                window.clearTimeout(timeoutId);
                checkScore = score;
            }
        }, 5000);
    })();

    world.step(1 / 60); //60 refreshes every second

    for (i = 0; i < trashC.length; i++) {
        scene.remove(trashT[i]);
        world.remove(trashC[i]);
    }

    playerMesh.position.copy(playerBody.position);
    playerMesh.quaternion.copy(playerBody.quaternion);

    var i;
    for (i = 0; i < meshes.length; i++) {
        var mesh = meshes[i];
        var body = bodies[i];

        mesh.position.copy(body.position);
        mesh.quaternion.copy(body.quaternion);
    }

    //update after user input
    if (moveLeft) {
        playerBody.velocity.y = 20;
        playerBody.position.z += 0.3;
        camera.position.y += 0.3;
        playerMesh.position.copy(playerBody.position);
    }
    if (moveRight) {
        playerBody.velocity.y = 20;
        playerBody.position.z -= 0.3;
        camera.position.y += 0.3;
        playerMesh.position.copy(playerBody.position);
    }

    //update camera
    camera.lookAt(playerBody.position);

    //debug
    //    cannonDebugRenderer.update();

    renderer.render(scene, camera);

    //score
    document.getElementById("GUI").innerHTML = "Score = " + score;
};

//restart after game ended
document.onclick = function () {
    if (end === true) {
        resetGame();
        camera.position.set(90, 2, 0);
        playerBody.position.set(0, 1.2, 0);
        update();
    }
};

window.addEventListener('load', init, false);