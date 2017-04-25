# Autoload

Want not care about loading classes, traits or interfaces? Aim of this development - is what you are looking for!

## Usage

Let module know about the objects. To do this, go to `*.info` file and configure the `autoload` directive were keys are subdirectories inside of the module directory and values - are namespace bases. As much as needed directories and namespace bases could be added by such way.

## Example

You able to use one of or both of known autoloading standards.

### PSR-0

```ini
; All objects, namespace path of which starts from "CTools",
; will be searched inside of "<MODULE_PATH>/psr-0".
autoload[psr-0][] = CTools
```

### PSR-4

```ini
; All objects, namespace path of which starts from "CTools\Plugins",
; will be searched inside of "<MODULE_PATH>/psr-4".
autoload[psr-4][] = CTools\Plugins
```
