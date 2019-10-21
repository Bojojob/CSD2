import simpleaudio as sa
import time
import random
import math

#

print("Initializing PolyGen")
program = ("on")

# create state variable and set program to start at initial state
state = ("input")

# create while loop to be able to switch between diffrent program states
while program == ("on"):
    while state == ("input"):
        # user sets bpm
        bpm = (input("Set bpm "))
        # user sets 2 timesignatures
        timeSig1 = (input("Set timesignature one as x/4, x = "))
        timeSig2 = (input("Set timesignature two as x/4, x = "))
        bars = input("How many bars would you like to generate? ")

        try:
            # checks if the input values aren't 0
            1 % float(bpm)
            1 % float(timeSig1)
            1 % float(timeSig2)
            1 % float(bars)
            # checks if the input values are positive
            math.sqrt(float(bpm))
            math.sqrt(float(timeSig1))
            math.sqrt(float(timeSig2))
            math.sqrt(float(bars))
            # checks if the input values can be converted to float
            val = float(bpm)
            val = float(timeSig1)
            val = float(timeSig2)
            val = float(bars)
        except:
            print("Something went wrong, please enter a positive number")
        else:
            print("Bpm set at " + str(bpm))
            print("Time signature one set as " + str(timeSig1) + "/4")
            print("Time signature two set as " + str(timeSig2) + "/8")

            quarterNoteDuration = 60 / float(bpm)
            # calculate the duration of a sixteenth note
            sixteenthNoteDuration = quarterNoteDuration / 4.0

            # timeSig1Steps = float(timeSig1) * (timeSig1[0] / timeSig2[2])

            # calculates how many 16th notes are in each time signature
            timeSig1Steps = float(timeSig1) * 4 * float(bars)
            timeSig2Steps = float(timeSig2) * 2 * float(bars)

            state = ("algorithm")

    while state == ("algorithm"):
        # create list where 'note timestamps' will be placed as 16th notes,
        # indicating at which time the sample must be played
        timestamps16thI1 = []
        timestamps16thI2 = []
        timestamps16thI3 = []

        # sets starting position for algorithm
        currentStep = 0

        print(timeSig1Steps)

        # HIERVAN FUNCTIE VAN MAKEN OM RUIMTE TE BESPAREN
        # creates note timestamps for instrument 1 sample algorithmicaly
        while currentStep < timeSig1Steps:
            # if currentstep is at the start of a bar,
            # fills step and advances two or three steps
            if currentStep % float(timeSig1) == 0:
                timestamps16thI1.append(currentStep)
                print(str(currentStep) + "Start filled kick")
                currentStep = currentStep + random.randint(2, 3)
            # chance to fill step and advance two or three steps
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI1.append(currentStep)
                print(str(currentStep) + "Chance filled kick")
                currentStep = currentStep + random.randint(2, 3)
            # if step not filled, advance two or three steps
            else:
                currentStep = currentStep + random.randint(2, 3)


        print(currentStep)
        # resets starting position for algorithm
        currentStep = 0

        while currentStep < timeSig1Steps:
            if currentStep % float(timeSig1) == 0:
                timestamps16thI2.append(currentStep)
                print(str(currentStep) + "Start filled conga")
                currentStep = currentStep + random.randint(2, 3)
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI2.append(currentStep)
                print(str(currentStep) + "Chance filled conga")
                currentStep = currentStep + random.randint(2, 3)
            else:
                currentStep = currentStep + random.randint(2, 3)

        print(currentStep)

        currentStep = 0

        while currentStep < timeSig1Steps:
            if currentStep % float(timeSig1) == 0:
                timestamps16thI3.append(currentStep)
                print(str(currentStep) + "Start filled bell")
                currentStep = currentStep + random.randint(2, 3)
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI3.append(currentStep)
                print(str(currentStep) + "Chance filled bell")
                currentStep = currentStep + random.randint(2, 3)
            else:
                currentStep = currentStep + random.randint(2, 3)

        print(currentStep)

        # create a list to hold the timestamps
        timestamps = []

        # creates a list to hold dictionarys
        dictList = []

        # VERWERKEN BINNEN FUNCTIE
        # transform the sixteenthTimestamps to time values
        # creates dictionary for time value and add to list
        for timestamp in timestamps16thI1:
          playTime = (timestamp * sixteenthNoteDuration)
          stamp = {'timestamp': playTime, 'instrument': 0}
          dictList.append(stamp)

        for timestamp in timestamps16thI2:
          playTime = (timestamp * sixteenthNoteDuration)
          stamp = {'timestamp': playTime, 'instrument': 1}
          dictList.append(stamp)

        for timestamp in timestamps16thI3:
          playTime = (timestamp * sixteenthNoteDuration)
          stamp = {'timestamp': playTime, 'instrument': 2}
          dictList.append(stamp)

        # sorts the list with dictonarys accoring to timestamp
        dictList = sorted(dictList, key = lambda i: i['timestamp'])

        # copys timestamps into a new list to be used later
        dictListBank = dictList.copy()

        # loads 3 audioFiles and store it into a list
        I0 = sa.WaveObject.from_wave_file("Kick.wav")
        I1 = sa.WaveObject.from_wave_file("Bell.wav")
        I2 = sa.WaveObject.from_wave_file("Conga.wav")
        samples = [I0, I1, I2]

        state = ("playSeq")


    while state == ("playSeq"):
        # how many time the sequence will be played
        loopAmount = 1

        for i in range(loopAmount):
            # pops the first dictionary off the list
            # pops payload out of the dictionary
            dictionary = dictList.pop(0)
            timestamp = dictionary['timestamp']
            sample = dictionary['instrument']

            # sets time/resets clock
            startTime = time.time()

            # play the sequence
            while True:
              # retrieve current time
              currentTime = time.time()

              # check whether the current time is beyond the timestamp's time,
              # meaning it is time to play the sample
              if(currentTime - startTime >= timestamp):
                samples[sample].play()

                # if there are timestamps left in the timestamps list
                if dictList:
                  # retrieve the next payload
                  dictionary = dictList.pop(0)
                  timestamp = dictionary['timestamp']
                  sample = dictionary['instrument']
                else:
                  # if there are no timestamps left in list,
                  # replenishes the timestamps list and breaks loop
                  dictList = list.copy(dictListBank)
                  time.sleep(quarterNoteDuration)
                  break

              else:
                # short wait to prevent we'll keep the processor busy when there's
                # nothing to do
                time.sleep(0.001)

            time.sleep(0.1)
            state = ("options")

    # if the sequence is finished
    while state == ("options"):
        # prints options
        print("To enter new parameters, enter 'reset'")
        print("To generate another rhythm with same parameters, enter 'reroll'")
        choice = str((input("To exit the program, enter 'exit' ")))

        # sets state according to input
        if choice == ("reset"):
            print("Resetting...")
            state = ("input")
        elif choice == ("reroll"):
            print("Rerolling...")
            state = ("algorithm")
        elif choice == ("exit"):
            print("Exiting program...")
            state = ("exit")
        else:
            print("Something went wrong")

    if state == ("exit"):
        break
