'use strict'

const fs = require('fs-extra')
const path = require('path')
const cfonts = require("cfonts")

const whitelist = [
	/^\.[A-Za-z0-9]*$/,
	/^node_modules$/,
];

const extToDel = [
	'',
	'.exe',
	'.in',
	'.out',
	'.txt',
	'.class',
	'.ans',
	'.table'
];

const size_limit = 10240;

function listFile(filePath) {
	fs.readdir(filePath, function (err, files) {
		if (err) {
			console.warn(err);
		} else {
			files.forEach(function (filename) {
				for (let whiteitem of whitelist) {
					if (whiteitem.test(filename)) return;
				}
				let file = path.join(filePath, filename);
				file = path.resolve(file);
				fs.stat(file, function (eror, stats) {
					if (eror) {
						console.warn('Access denied.');
					} else {
						const isFile = stats.isFile();
						const isDir = stats.isDirectory();
						const size = stats.size;
						if (isFile) {
							if (extToDel.includes(path.extname(file))) {
								console.log(`${file} has been deleted.`);
								fs.unlinkSync(file);
							}
							if (size > size_limit) {
								console.log(`${file} will be moved to workspace/tmp because of its size`);
								fs.ensureDirSync(path.join(__dirname, "tmp/"));
								fs.moveSync(file, path.join(__dirname, "tmp", filename));
							}
						}
						if (isDir) {
							listFile(file);
						}
					}
				})
			});
		}
	});
}

cfonts.say("source-|contest", { colors: ["yellow"] });

listFile('.');