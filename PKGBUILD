# Maintainer: SzChurros
pkgname=brik
pkgver=1.1.0
pkgrel=1
pkgdesc="Awful build automation tool"
arch=('x86_64')
url="https://github.com/SzChurros/brik"
license=('MIT')
depends=()
makedepends=('gcc')
source=("$url/archive/refs/tags/v$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$pkgname-$pkgver"
    ./build.sh
}

package() {
    cd "$pkgname-$pkgver"
    install -Dm755 bin/brik "$pkgdir/usr/bin/brik"
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
