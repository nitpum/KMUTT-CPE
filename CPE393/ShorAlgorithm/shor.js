// Input
const number = process.argv.slice(1)[1]
// We can't -1.mod so we have to use variable
const negative = -1
Number.prototype.mod = function(n) {
  return ((this % n) + n) % n
}

const main = async () => {
  var p = 1
  var q = number
  console.log(`Number[X] is ${number}`)
  do {
    do {
      do {
        var a = await guessA()
        var gcd = await GCD(a, number)
        if (gcd != 1) {
          // Lucky, we found a co-prime
          const p = gcd
          const q = number / p
          answer(p, q)
          return
        }
        var r = await findPeriod(a, number)
        console.log(`Period: ${r}`)
      } while (r % 2 != 0) // r must be even
    } while ((Math.pow(a, r / 2) + 1) % number == negative.mod(number))
    var x = await (Math.pow(a, r / 2) + 1)
    var y = await (Math.pow(a, r / 2) - 1)
    p = await GCD(number, x)
    q = await GCD(number, y)
  } while ((p == 1 && q == number) || (p == number && q == 1))
  answer(p, q)
}

const answer = (p, q) => console.log(`Answer P: ${p} | Q: ${q}`)

const guessA = async () => {
  const a = await randomNumber(2, number - 1)
  const gcd = await GCD(a, number)
  console.log(`Guess[a]: ${a} | GCD: ${gcd}`)
  return a
}

const randomNumber = async (min, max) => {
  var value = Math.floor(Math.random() * max)
  while (value < min || value > max) {
    value = Math.floor(Math.random() * max)
  }
  return value
}

const findPeriod = async (a, n) => {
  let log = []
  for (let r = 0; true; r++) {
    let ar = Math.pow(a, r)
    let remaining = ar % n
    console.log(`r: ${r} | a^r: ${ar}\t\t|\tremaining: ${remaining}`)
    if (log.includes(remaining)) return r
    log = [...log, remaining]
  }
}

const GCD = async (a, b) => {
  if (a % b == 0) return b
  else return GCD(b, a % b)
}

main()
