if($args.count -eq 0){
	Write-Host "Improper Command line arguments"
	Write-Host "use: powershellScript (outputFileDir from current Directory) outputFileName IntialSearchPath (keep blank if you wish for it to be the cwd)"
	Write-Host
	exit
}

$global:readIntoArray = $TRUE
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

$oldFileLines

if(!(Test-Path $outFile)){
	$readIntoArray = $FALSE
	Write-Host "Creating new header file"
	Write-Host
	New-Item -path $outFileDir -name $outFileName -type "file"
}
else{
	foreach($line in [System.IO.File]::ReadLines($outFile)){
		#Write-Host $line
		$oldFileLines += @($line)
	}
	#$oldFileLines
}
#Write-Host "Writing to header file " + $outFile
#Write-Host

function AddIncludesRecursively($outFilePath, $outFileName, $Folder, $PathExtension,$oldLines, $newLines){
	$files = Get-ChildItem $Folder *.h
	$subFolders = Get-ChildItem $Folder -Directory

	if(!($PathExtension -eq "")){
		#Write-Host "current include extension: "$PathExtension
		$PathExtension = $PathExtension + "\"
	}

	#Write-Host "read into array: " $global:readIntoArray

	foreach($file in $files){
		if(!($file.Name -eq $outFileName)){
			#Write-Host "Include being generated for header file: " $PathExtenSion$file
			$currentLine = '#include "'+  $PathExtension +  $file + '"'
			#Write-Host "current line: " $currentLine
			if($global:readIntoArray -eq $FALSE){
				#'#include "'+  $PathExtension +  $file + '"' >> $outFilePath
				$currentLine >> $outFilePath
			}
			else{
				$global:readIntoArray = $FALSE
				foreach($line in $oldLines){
					if($line -eq $currentLine){
						$global:readIntoArray = $TRUE
						break
					}
				}
				$newLines += $currentLine

				if($global:readIntoArray -eq $FALSE){
					Write-Host "Discrepency in output file, creating new output file"
					Clear-Content $outFilePath
					foreach($line in $newLines){
						$line >> $outFilePath
					}
				}
			}
		}
	}

	foreach($subFolder in $subFolders){
		$SubPathExtension = $PathExtension + $subFolder
		AddIncludesRecursively $outFile $outFileName ($Folder + "/" + $subFolder) $SubPathExtension $oldLines $newLines
	}
}

#Write-Host "Generating master header file"
$ReadLines = @("#pragma once")
#"#pragma once" > $outFile

AddIncludesRecursively $outFile $args[1] ($args[0] + "/" + $args[2]) $initialExtension $oldFileLines $ReadLines