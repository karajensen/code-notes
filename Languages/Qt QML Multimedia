/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML MULTIMEDIA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QtMultimedia.availableCameras
QtMultimedia.defaultCamera
QtMultimedia.convertVolume(volume, from, to)

------------------------------------------------------------------------------------------------------------
    
// CAMERA
// import QtMultimedia 5.8, Inherits QtObject
// Access viewfinder frames, and take photos and movies
Camera {
    availability
    cameraState
    cameraStatus
    captureMode
    deviceId
    digitalZoom
    displayName
    errorCode
    errorString
    lockStatus
    maximumDigitalZoom
    maximumOpticalZoom
    mediaObject
    metaData.cameraManufacturer
    metaData.cameraModel
    metaData.event
    metaData.subject
    metaData.orientation
    metaData.dateTimeOriginal
    metaData.gpsLatitude
    metaData.gpsLongitude
    metaData.gpsAltitude
    metaData.gpsTimestamp
    metaData.gpsTrack
    metaData.gpsSpeed
    metaData.gpsImgDirection
    metaData.gpsProcessingMethod
    opticalZoom
    orientation
    position
    viewfinder.resolution
    viewfinder.minimumFrameRate
    viewfinder.maximumFrameRate
    onCameraStateChanged: { state }
    onDigitalZoomChanged: { zoom }
    onError: { errorCode, errorString }
    onLockStatusChanged: {}
    onManualWhiteBalanceChanged: { qreal }
    onMaximumDigitalZoomChanged: { zoom }
    onMaximumOpticalZoomChanged: { zoom }
    onOpticalZoomChanged: { zoom }
    onWhiteBalanceModeChanged: { Camera::WhiteBalanceMode }
    
    // CameraCapture
    // Cannot be instantiated, only a child of Camera
    imageCapture {
        capturedImagePath
        errorString
        ready
        resolution
        supportedResolutions
        onCaptureFailed: { requestId, message }
        onImageCaptured: { requestId, preview }
        onImageMetadataAvailable: { requestId, key, valu }
        onImageSaved: { requestId, path }
    }
    
    // CameraExposure 
    // Cannot be instantiated, only a child of Camera
    exposure {
        aperture
        exposureCompensation
        exposureMode
        iso
        manualAperture
        manualIso 
        manualShutterSpeed
        meteringMode
        shutterSpeed
        spotMeteringPoint
        supportedExposureModes
    }
    
    // CameraFlash
    // Cannot be instantiated, only a child of Camera
    flash {
        mode
        ready
        supportedModes
    }
    
    // CameraFocus
    // Cannot be instantiated, only a child of Camera
    focus {
        customFocusPoint
        focusMode
        focusPointMode
        focusZones
        supportedFocusModes
        supportedFocusPointModes
    }
    
    // CameraImageProcessing 
    // Cannot be instantiated, only a child of Camera    
    imageProcessing {
        brightness
        colorFilter
        contrast
        denoisingLevel
        isAvailable
        manualWhiteBalance
        saturation
        sharpeningLevel
        supportedColorFilters
        supportedWhiteBalanceModes
        whiteBalanceMode
    }
    
    // CameraRecorder 
    // Cannot be instantiated, only a child of Camera    
    videoRecorder {
        actualLocation
        audioBitRate
        audioChannels
        audioCodec
        audioEncodingMode
        audioSampleRate
        duration
        errorCode 
        errorString
        frameRate
        mediaContainer
        muted
        outputLocation
        recorderState
        recorderStatus
        resolution
        videoBitRate 
        videoCodec
        videoEncodingMode
    }
}

camera.searchAndLock()
camera.start()
camera.stop()
camera.supportedViewfinderFrameRateRanges(resolution)
camera.supportedViewfinderResolutions(minimumFps, maximumFps)
camera.unlock()
    
camera.imageCapture.cancelCapture()
camera.imageCapture.capture()
camera.imageCapture.captureToLocation(location)
camera.imageCapture.setMetadata(key, value)
    
camera.exposure.setAutoAperture()
camera.exposure.setAutoIsoSensitivity()
camera.exposure.setAutoShutterSpeed()

camera.flash.flashModeChanged(int)
camera.flash.flashReady(bool)

camera.videoRecorder.record()
camera.videoRecorder.setMetadata(key, value)
camera.videoRecorder. stop()

------------------------------------------------------------------------------------------------------------

// MEDIAPLAYER
// import QtMultimedia 5.8
// Add media playback to a scene
MediaPlayer {
}

------------------------------------------------------------------------------------------------------------

// VIDEO
// import QtMultimedia 5.8, Inherits Item
// A convenience type for showing a specified video
Video {
}

------------------------------------------------------------------------------------------------------------

// VIDEOOUTPUT
// import QtMultimedia 5.8
// Render video or camera viewfinder
VideoOutput {
}

