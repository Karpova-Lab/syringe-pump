#!/bin/bash

# Set source (USB drive) and destination (desktop) paths
SOURCE="/Users/lustiga/Dropbox (HHMI)/Code/karpova_lab/pyControl/Hardware Modules/Syringe/mcad/sheet-metal"  # Change this to the actual name of your USB drive
DESTINATION="/Users/lustiga/Dropbox (HHMI)/Code/karpova_lab/pyControl/Hardware Modules/Syringe/mkdocs/src/pump/cad"

# Check if USB drive is mounted
if [ ! -d "$SOURCE" ]; then
    echo "USB drive not found. Please check the drive name and ensure it's mounted."
    exit 1
fi

# Copy the files from USB to Desktop if they exist
# Copy all files from source to destination
cp -r "$SOURCE"/* "$DESTINATION"
echo "All files copied from $SOURCE to $DESTINATION"
