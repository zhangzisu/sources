'use strict'

const fs = require('fs-extra')
const path = require('path')
const cfonts = require("cfonts")

const whitelist = [
	/^\.[A-Za-z0-9]*$/,
	/^node_modules$/,
	/^bigfiles$/
];

const extToKeep = [
	/^\.c(c|pp|xx|s)?$/i,
	/^\.j(ava|s|son)$/i,
	/^\.h[a-z]*$/i,
	/^\.pyo?$/i,
	/^\.sh?$/i,
	/^\.bat?$/i,
	/^\.m(d|arkdown)$/i,
	/^\.[a-z]+ml$/i,
	/^\.ps[0-9]?$/i
];

const size_limit = 50 * 1024;     // 50KB

function match(list, string) {
	for (let item of list) {
		if (item.test(string)) return true;
	}
	return false;
}

function listFile(filePath) {
	fs.readdir(filePath, function (err, files) {
		if (err) {
			console.warn(err);
		} else {
			files.forEach(function (filename) {
				if (match(whitelist, filename)) return;
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
							if (!match(extToKeep, path.extname(file))) {
								console.log(`${file} has been deleted.`);
								fs.unlinkSync(file);
							} else if (size > size_limit) {
								console.log(`${file} will be moved to workspace/bigfiles because of its size`);
								fs.ensureDirSync(path.join(__dirname, "bigfiles"));
								fs.moveSync(file, path.join(__dirname, "bigfiles", filename));
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