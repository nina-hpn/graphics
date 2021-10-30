 
var init = () => {
    var scene = new THREE.Scene();

    var  enableFog = false;
    if (enableFog) {

        scene.fog = new THREE.FogExp2(0xfffffff, 0.2);
    }

    //Shape objects
    var box = getBox(1, 1, 1, color='rgb(120,120,120)');
    box.name = 'box-1'
    

    var plane = getPlane(7);
    //The name can be called on the parent object
    plane.name = 'plane-1';


    var sphere = Sphere(2, 2, 5);
    sphere.name = 's-1'

    var sphere2 = getSphere(0.05, 's-2', 'rgb(255,255,255)', material='basic')

    // Lighting object
    var pointLight = getPointLight(0xffffff, 1);
    pointLight.position.y = 3

    // Animation
    box.position.y = box.geometry.parameters.height/2;
    plane.rotation.x = Math.PI/2;

    pointLight.add(sphere2);
    scene.add(pointLight);
    scene.add(box);  
    scene.add(sphere);
    scene.add(plane);

    var camera = new THREE.PerspectiveCamera(
        75,
        window.innerWidth/window.innerHeight,
        0.1, 
        1000
    );


    var renderer = new THREE.WebGLRenderer();
    renderer.setSize(
        window.innerWidth,
        window.innerHeight
    );
    renderer.setClearColor('rgb(120, 120, 120)');


    document.body.appendChild(renderer.domElement);

    var controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.minDistance = 1;
    controls.maxDistance = 1000;
    camera.position.set( 5, 2, 1 );
    controls.update();

    document.getElementById('webgl').appendChild(renderer.domElement);
    update(renderer, scene, camera)

    return scene
}

// Creating shape function

function getBox(w, h, d, name=false, material='phong', color=0xffffff) {
    var geometry = new THREE.BoxGeometry(w, h, d);

    if (material == 'phong') {
        
        var material = new THREE.MeshPhongMaterial({
            color: color
        });
    }
    else if (material == 'basic') {
        var material = new THREE.MeshBasicMaterial({
            color: color
        })
    }
    var mesh = new THREE.Mesh(
        geometry,
        material
    );

    if( name != false) {
        mesh.name = name
    }

    return mesh;
}

function Sphere(r, w, h) {
    var geometry = new THREE.SphereGeometry(r, w, h);
    
    var material = new THREE.MeshBasicMaterial({
        wireframe: true, 
        color: 0xff9999
    });

    var sphere = new THREE.Mesh(
        geometry,
        material
    );

    return sphere;
}

function getSphere(size, name=false, color=0xffffff, material='phong', resolution=(24, 24)) {
    var geometry = new THREE.SphereGeometry(size, resolution[0], resolution[1]);
    if (material == 'phong') {
        
        var material = new THREE.MeshPhongMaterial({
            color: color
        });
    }
    else if (material == 'basic') {
        var material = new THREE.MeshBasicMaterial({
            color: color
        })
    }
    var mesh = new THREE.Mesh(
        geometry,
        material
    );

    if( name != false) {
        mesh.name = name
    }

    return mesh;
}

function getPlane (size, name=false) {
    var geometry = new THREE.PlaneGeometry(size, size);

    var material = new THREE.MeshPhongMaterial({
        color: 'rgb(120, 120, 120)',
        side: THREE.DoubleSide
    });
    var mesh = new THREE.Mesh(
        geometry,
        material
    );
    if (name != false) {
        mesh.name = name
    }

    return mesh;
}

function getHeart (x, y, name=false) {
    const heartShape = new THREE.Shape();
    heartShape.moveTo( x + 5, y + 5 );

    heartShape.bezierCurveTo( x + 5, y + 5, x + 4, y, x, y );
    heartShape.bezierCurveTo( x - 6, y, x - 6, y + 7,x - 6, y + 7 );
    heartShape.bezierCurveTo( x - 6, y + 11, x - 3, y + 15.4, x + 5, y + 19 );
    heartShape.bezierCurveTo( x + 12, y + 15.4, x + 16, y + 11, x + 16, y + 7 );
    heartShape.bezierCurveTo( x + 16, y + 7, x + 16, y, x + 10, y );
    heartShape.bezierCurveTo( x + 7, y, x + 5, y + 5, x + 5, y + 5 );
    
    var geometry = new THREE.ShapeGeometry( heartShape );
    var material = new THREE.MeshBasicMaterial({ 
        color: 0x00ff00 
    });

    if (name != false) {
        mesh.name = name
    }
    var mesh = new THREE.Mesh( geometry, material ) ;
}

// Animation function

function rotate(name, parent, x = 0, y = 0, z = 0) {
    /**
     * Rotating function
     * Args:
     * name: name of the object we want to rotate
     * parent: parent object of the one we pick
     * x, y, z: the degree we want to change
     */

    var object = parent.getObjectByName(name);

    object.rotation.x += x;
    object.rotation.y += y;
    object.rotation.z += z;
}

function scale(name, parent, x = 1, y = 1, z = 1){

    /**
     * Scaling function
     * Args:
     * name: name of the object we want to scale
     * parent: parent object of the one we pick
     * x, y, z: the size we want to change
     */
    var object = parent.getObjectByName(name);

    object = object.scale.set(x, y, z);
    
}

function position(name, parent, x =0 , y =0 , z =0){

    /**
     * Translate function
     * Args:
     * name: name of the object we want to move 
     * parent: parent object of the one we pick
     * x, y, z: the position we want to go to
     */
    var object = parent.getObjectByName(name);

    object = object.position.set(x, y, z);
}

// Update function for continuosly rendering

function update(renderer, scene, camera) {

    renderer.render(
        scene,
        camera
    );

    scale('box-1', scene, 0.5, 0.2, 1);
    rotate('box-1', scene, x=0.01, z = 0.02);
    //position('box-1', scene, 0, 2, 3);

    position('s-1', scene, -2, 2, -2);
    rotate('s-1', scene, x=0.01, z = 0.02);

    requestAnimationFrame(function() {

        //Get a callback in the recursive manner
        //Like the setInterval()
        //Continuosly rendering 

        update(renderer, scene, camera);
    })
}

// Lighting function 

function getPointLight(color, intensity) {
    var light = new THREE.PointLight(color, intensity);

    return light;
}


var scene = init();

