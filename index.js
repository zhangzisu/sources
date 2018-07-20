'use strict'

const fs = require('fs');
const path = require('path')

let ignore = [
	'.git',
	'.vscode',
	'node_modules'
];

let extToDel = [
	'',
	'.exe',
	'.in',
	'.out',
	'.txt',
	'.class',
	'.ans'
];

function listFile(filePath) {
	fs.readdir(filePath, function (err, files) {
		if (err) {
			console.warn(err);
		} else {
			files.forEach(function (filename) {
				let file = path.join(filePath, filename);
				file = path.resolve(file);
				fs.stat(file, function (eror, stats) {
					if (eror) {
						console.warn('Access denied.');
					} else {
						let isFile = stats.isFile();
						let isDir = stats.isDirectory();
						if (isFile) {
							if (extToDel.includes(path.extname(file))) {
								console.log(`${file} has been deleted.`);
								fs.unlinkSync(file);
							}
						}
						if (isDir) {
							if (!ignore.includes(filename))
								listFile(file);
						}
					}
				})
			});
		}
	});
}

listFile('.');