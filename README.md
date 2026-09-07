# Source 2013 studiomdl

This repo contains the **studiomdl** code for Source 2013, based on the [2006 Episode 1 SDK](https://github.com/Source-SDK-Archives/source-sdk-2006-ep1/tree/master/utils/studiomdl), with compatibility fixes for **Windows** **x86** and **x64**.

## Integrating
Add the following to **vpc_scripts/projects.vgc**:
```
$Project "studiomdl"
{
	"utils\studiomdl\studiomdl.vpc" [$WINDOWS]
}
```

Then, in **vpc_scripts/groups.vgc**, add `"studiomdl"` to the group of your choice.

## Notes
The code of studiomdl has been obtained **legally** from the [2006 Episode 1 SDK](https://github.com/Source-SDK-Archives/source-sdk-2006-ep1/tree/master/), 
initially adapted by **InevitablyDivinity** for **Source SDK 2013 x86** and later fixed by **Unusuario2** for x64 builds with minor code cleanups.
