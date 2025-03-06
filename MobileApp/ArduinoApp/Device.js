import React, { useState, useEffect } from 'react';
import { 
  StyleSheet,
  Text, 
  View, 
  Image,
  TouchableOpacity, 
  ImageBackground,
  TextInput
} from 'react-native';

function Device({ deviceID, isAnimalDetected, location, Distance }) {
    return (
        <View style={[styles.mainContainer, {borderColor: isAnimalDetected ? "rgba(255,0,0,0.8)" : "rgba(0,255,0,0.4)"}]}>
            {/* Left Section - Image */}
            <Image 
                source={require('./assets/monitoring.png')} 
                style={styles.icon} 
            />
            {/* Text Section - Text Info */}
            <View style={styles.textContainer}>
                <Text style={styles.deviceIdText}>ID: {deviceID}</Text>
                <Text style={styles.deviceIdText}>Location: {location}</Text>
                <Text style={styles.deviceIdText}>Distance: {Distance}m</Text>
                <Text style={styles.deviceIdText}>
                    Status: {isAnimalDetected ? "Detected" : "Safe"}
                </Text>
            </View>

            <Text style={{fontSize: isAnimalDetected ? 60 : 28, color: isAnimalDetected? "#ff0000": "#00ff00", fontWeight: 'bold' }}>{(isAnimalDetected? "⚠" : "✅")}</Text>
        </View>
    );
}

const styles = StyleSheet.create({
    mainContainer: {
        flexDirection: 'row',  // Arrange items in a row
        alignItems: 'center',  // Align items vertically centered
        justifyContent: 'space-between', // Pushes text to the left and image to the right
        marginHorizontal: 10,
        marginBottom: 10,
        padding: 20,
        backgroundColor: 'rgba(201, 227, 227, 0.8)',
        borderRadius: 20,
        borderWidth: 2,
    },
    textContainer: {
        flex: 1,  // Takes available space next to the image
    },
    icon: {
        width: 70, // Adjust width as needed
        height: '100%', // Fills the available height
        resizeMode: 'contain', // Keeps aspect ratio
        marginRight: 20,
    },
    deviceIdText: {
        fontSize: 16,
        fontWeight: 'bold',
        marginBottom: 5,
    },
    statusGood:{
        fontSize: 30,
        fontWeight: 'bold',
    }
});

export default Device;
