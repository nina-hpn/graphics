export function getBox(w, h, d) {
    var geometry = new THREE.BoxGeometry(w, h, d);

    var material = new THREE.MeshBasicMaterial({
        color: 0x00ff00
    });
    var mesh = new THREE.Mesh(
        geometry,
        material
    );

    return mesh;
}

export function getPlane (size) {
    var geometry = new THREE.PlaneGeometry(size, size);

    var material = new THREE.MeshBasicMaterial({
        color: 0xff0000,
        side: THREE.DoubleSide
    });
    var mesh = new THREE.Mesh(
        geometry,
        material
    );

    return mesh;
}

export function getHeart (x, y) {
    var geometry = new THREE.ShapeGeometry( heartShape );
    var material = new THREE.MeshBasicMaterial({ 
        color: 0x00ff00 
    });
    var mesh = new THREE.Mesh( geometry, material ) ;
}