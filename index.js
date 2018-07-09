function match(gA, gB) {
    gA.sort((a, b) => { return a.id > b.id; });
    gB.sort((a, b) => { return a.id > b.id; });
    let idA = 0, idB = 0;
    while (idA < gA.length && idB < gB.length) {
        if (gA[idA].id === gB[idB].id) return true;
        if (gA[idA].id < gB[idB].id) idA++;
        else idB++;
    }
    return false;
}

console.log(match([{ id: 2 }, { id: 3 }, { id: 4 }], [{ id: 2 }]));