if($args.count -eq 0){
	Write-Host "Improper Command line arguments"
	Write-Host "use: powershellScript (outputFileDir from current Directory) outputFileName IntialSearchPath (keep blank if you wish for it to be the cwd)"
	Write-Host
	exit
}

$initialExtension = ""
if($args.count -eq 3){
	$initialExtension = $args[2]
}
$cwd = Get-Location

if(!(Test-Path ($cwd.Path + "\" + $args[0]))){
	Write-Host "output File Directory does not exist! now exiting"
	Write-Host
	exit
}

#Write-Host $args[0]
#Write-Host $args[1]
#Write-Host $args[2]

$outFileDir = $cwd.Path + "\" + $args[0]
#$outFileName = $args[1]
$outFile = $outFileDir + "\" + $args[1]

if(!(Test-Path $outFile)){
	Write-Host "Creating new header file"
	Write-Host
	New-Item -path $outFileDir -name $outFileName -type "file"
}
#Write-Host "Writing to header file " + $outFile
#Write-Host

function AddIncludesRecursively($outFilePath, $outFileName, $Folder, $PathExtension){
	$files = Get-ChildItem $Folder *.h
	$subFolders = Get-ChildItem $Folder -Directory

	if(!($PathExtension -eq "")){
		#Write-Host "current include extension: "$PathExtension
		$PathExtension = $PathExtension + "\"
	}
	#else{
		#Write-Host "No Include Extension"
	#}

	foreach($file in $files){
		if(!($file.Name -eq $outFileName)){
			#Write-Host "Include being generated for header file: " $PathExtenSion$file
			'#include "'+  $PathExtension +  $file + '"' >> $outFilePath
		}
	}

	foreach($subFolder in $subFolders){
		$SubPathExtension = $PathExtension + $subFolder
		AddIncludesRecursively $outFile $outFileName ($Folder + "/" + $subFolder) $SubPathExtension
	}
}

#Write-Host "Generating master header file"
"#pragma once" > $outFile

AddIncludesRecursively $outFile $args[1] ($args[0] + "/" + $args[2]) $initialExtension