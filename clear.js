'use strict'

const fs = require('fs-extra')
const path = require('path')
const cfonts = require("cfonts")

const whitelist = [
	/^\..*$/,
	/^node_modules$/,
	/^bigfiles$/,
	/^yarn\.lock$/,
	/\.c(c|pp|xx|s)?$/i,
	/\.j(ava|s|son)$/i,
	/\.h[a-z]*$/i,
	/\.pyo?$/i,
	/\.sh$/i,
	/\.bat$/i,
	/\.m(d|arkdown)$/i,
	/\.[a-z]+ml$/i,
	/\.ps[0-9]?$/i
]

/**
 * Match str in a regexp list
 * @param {RegExp[]} list
 * @param {string} str
 * @returns {boolean}
 */
function match(list, str) {
	return list.reduce((p, c) => (p || c.test(str)), false)
}

/**
 * List and remove unecessary files
 * @param {string} root
 */
function listAndRemove(root) {
	fs.readdir(root, function (err, files) {
		if (err) {
			console.warn(err)
		} else {
			files.forEach(function (filename) {
				if (match(whitelist, filename)) return
				let fullpath = path.join(root, filename)
				fullpath = path.resolve(fullpath)
				const stats = fs.statSync(fullpath)
				const isDir = stats.isDirectory()
				if (isDir) {
					listAndRemove(fullpath)
					if (!fs.readdirSync(fullpath).length) {
						fs.removeSync(fullpath)
					}
				} else {
					console.log(`${fullpath} has been deleted.`)
					fs.unlinkSync(fullpath)
				}
			})
		}
	})
}

cfonts.say("source|OnlineJudge", { colors: ["yellow"] })

listAndRemove('.')
