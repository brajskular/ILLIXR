#pragma once

#include <iostream>
#include <chrono>
#include <memory>
#include <boost/optional.hpp>

#include <opencv2/core/mat.hpp>
#undef Success // For 'Success' conflict
#include <eigen3/Eigen/Dense>
#include <GL/gl.h>
//#undef Complex // For 'Complex' conflict
#include "phonebook.hpp" 
#include "switchboard.hpp"
#include "relative_clock.hpp"

// Tell gldemo and timewarp_gl to use two texture handle for left and right eye
#define USE_ALT_EYE_FORMAT

namespace ILLIXR {

	using ullong = unsigned long long;

	// Data type that combines the IMU and camera data at a certain timestamp.
	// If there is only IMU data for a certain timestamp, img0 and img1 will be null
	// time is the current UNIX time where dataset_time is the time read from the csv
	struct imu_cam_type : public switchboard::event {
		time_point time;
		Eigen::Vector3f angular_v;
		Eigen::Vector3f linear_a;
		std::optional<cv::Mat> img0;
		std::optional<cv::Mat> img1;
		imu_cam_type(time_point time_,
					 Eigen::Vector3f angular_v_,
					 Eigen::Vector3f linear_a_,
					 std::optional<cv::Mat> img0_,
					 std::optional<cv::Mat> img1_)
			: time{time_}
			, angular_v{angular_v_}
			, linear_a{linear_a_}
			, img0{img0_}
			, img1{img1_}
		{ }
	};

	struct imu_cam_type_prof : public switchboard::event {
		int frame_id;
		time_point time;
		time_point start_time; // Time that the device sent the packet
		time_point rec_time; // Time the device received the packet
		time_point dataset_time; // Time from dataset
		long int created_time; // Time the imu and camera data is put to the switchboard
		Eigen::Vector3f angular_v;
		Eigen::Vector3f linear_a;
		std::optional<cv::Mat> img0;
		std::optional<cv::Mat> img1;
		imu_cam_type_prof(int frame_id_,
					 time_point time_,
					 time_point start_time_,
					 time_point rec_time_,
					 time_point dataset_time_,
					 long int created_time_,
					 Eigen::Vector3f angular_v_,
					 Eigen::Vector3f linear_a_,
					 std::optional<cv::Mat> img0_,
					 std::optional<cv::Mat> img1_)
			: frame_id{frame_id_}
			, time{time_}
			, start_time{start_time_}
			, rec_time{rec_time_}
			, dataset_time{dataset_time_}
			, created_time{created_time_} 
			, angular_v{angular_v_}
			, linear_a{linear_a_}
			, img0{img0_}
			, img1{img1_}
		{ }
	};

	struct connection_signal : public switchboard::event {
		bool start;

		connection_signal(bool start_)
			: start{start_}
		{ }
	};

	struct imu_type {
		time_point timestamp;
		Eigen::Matrix<double, 3, 1> wm;
		Eigen::Matrix<double, 3, 1> am;


		imu_type(
				time_point timestamp_,
				Eigen::Matrix<double, 3, 1> wm_,
				Eigen::Matrix<double, 3, 1> am_
				)
			: timestamp{timestamp_}
			, wm{wm_}
			, am{am_}
		{ }
	};

	struct imu_buffer : public switchboard::event {
		std::vector<imu_type> imus;
		imu_buffer(std::vector<imu_type> imus_)
			: imus{imus_}
		{ }
	};

    class rgb_depth_type : public switchboard::event {
        [[maybe_unused]] time_point time;
        std::optional<cv::Mat> rgb;
        std::optional<cv::Mat> depth;
	public:
		rgb_depth_type(time_point _time,
					   std::optional<cv::Mat> _rgb,
					   std::optional<cv::Mat> _depth
					   )
			: time{_time}
			, rgb{_rgb}
			, depth{_depth}
		{ }
    };

	// Values needed to initialize the IMU integrator
	typedef struct {
		double gyro_noise;
		double acc_noise;
		double gyro_walk;
		double acc_walk;
		Eigen::Matrix<double,3,1> n_gravity;
		double imu_integration_sigma;
		double nominal_rate;
	} imu_params;

	// IMU biases, initialization params, and slow pose needed by the IMU integrator
	struct imu_integrator_input : public switchboard::event {
		time_point last_cam_integration_time;
		duration t_offset;
		imu_params params;
		
		Eigen::Vector3d biasAcc;
		Eigen::Vector3d biasGyro;
		Eigen::Matrix<double,3,1> position;
		Eigen::Matrix<double,3,1> velocity;
		Eigen::Quaterniond quat;
		long int timestamp;

		imu_integrator_input()
			: last_cam_integration_time{time_point{}}
			, t_offset{duration(std::chrono::milliseconds{-50})}
			, params{.gyro_noise = 0.00016968,
				.acc_noise = 0.002,
				.gyro_walk = 1.9393e-05,
				.acc_walk = 0.003,
				.n_gravity = Eigen::Matrix<double,3,1>(0.0, 0.0, -9.81),
				.imu_integration_sigma = 1.0,
				.nominal_rate = 200.0,}
			, biasAcc{Eigen::Vector3d{0, 0, 0}}
			, biasGyro{Eigen::Vector3d{0, 0, 0}}
			, position{Eigen::Vector3d{0, 0, 0}}
			, velocity{Eigen::Vector3d{0, 0, 0}}
			, quat{Eigen::Quaterniond{1, 0, 0, 0}}
			, timestamp{0}
		{ }
		imu_integrator_input(
							 time_point last_cam_integration_time_,
							 duration t_offset_,
							 imu_params params_,
							 Eigen::Vector3d biasAcc_,
							 Eigen::Vector3d biasGyro_,
							 Eigen::Matrix<double,3,1> position_,
							 Eigen::Matrix<double,3,1> velocity_,
							 Eigen::Quaterniond quat_
							 )
			: last_cam_integration_time{last_cam_integration_time_}
			, t_offset{t_offset_}
			, params{params_}
			, biasAcc{biasAcc_}
			, biasGyro{biasGyro_}
			, position{position_}
			, velocity{velocity_}
			, quat{quat_}
			, timestamp{0}
		{ }
	};

	// Output of the IMU integrator to be used by pose prediction
	struct imu_raw_type : public switchboard::event {
		// Biases from the last two IMU integration iterations used by RK4 for pose predict
		Eigen::Matrix<double,3,1> w_hat;
		Eigen::Matrix<double,3,1> a_hat;
		Eigen::Matrix<double,3,1> w_hat2;
		Eigen::Matrix<double,3,1> a_hat2;

		// Faster pose propagated forwards by the IMU integrator
		Eigen::Matrix<double,3,1> pos;
		Eigen::Matrix<double,3,1> vel;
		Eigen::Quaterniond quat;
		time_point imu_time;
		imu_raw_type(Eigen::Matrix<double,3,1> w_hat_,
					 Eigen::Matrix<double,3,1> a_hat_,
					 Eigen::Matrix<double,3,1> w_hat2_,
					 Eigen::Matrix<double,3,1> a_hat2_,
					 Eigen::Matrix<double,3,1> pos_,
					 Eigen::Matrix<double,3,1> vel_,
					 Eigen::Quaterniond quat_,
					 time_point imu_time_)
			: w_hat{w_hat_}
			, a_hat{a_hat_}
			, w_hat2{w_hat2_}
			, a_hat2{a_hat2_}
			, pos{pos_}
			, vel{vel_}
			, quat{quat_}
			, imu_time{imu_time_}
		{ }
	};

	struct pose_type : public switchboard::event {
		time_point sensor_time; // Recorded time of sensor data ingestion
		Eigen::Vector3f position;
		Eigen::Quaternionf orientation;
		pose_type()
			: sensor_time{time_point{}}
			, position{Eigen::Vector3f{0, 0, 0}}
			, orientation{Eigen::Quaternionf{1, 0, 0, 0}}
		{ }
		pose_type(time_point sensor_time_,
				  Eigen::Vector3f position_,
				  Eigen::Quaternionf orientation_)
			: sensor_time{sensor_time_}
			, position{position_}
			, orientation{orientation_}
		{ }
	};

	struct pose_type_prof : public switchboard::event {
		int frame_id;
		time_point sensor_time; // Recorded time of sensor data ingestion
		time_point start_time; // Recorded time of transfer start
		time_point rec_time; // When the server received the packet (in server time)
		time_point dataset_time; // Sensor time
		Eigen::Vector3f position;
		Eigen::Quaternionf orientation;
		pose_type_prof()
			: frame_id{0}
			, sensor_time{time_point{}}
			, start_time{time_point{}}
			, rec_time{time_point{}}
			, dataset_time{time_point{}}
			, position{Eigen::Vector3f{0, 0, 0}}
			, orientation{Eigen::Quaternionf{1, 0, 0, 0}}
		{ }
		pose_type_prof(int frame_id_,
				  time_point sensor_time_,
				  time_point start_time_,
				  time_point rec_time_,
				  time_point dataset_time_,
				  Eigen::Vector3f position_,
				  Eigen::Quaternionf orientation_)
			: frame_id{frame_id_}
			, sensor_time{sensor_time_}
			, start_time{start_time_}
			, rec_time{rec_time_}
			, dataset_time{dataset_time_}
			, position{position_}
			, orientation{orientation_}
		{ }
	};

	typedef struct {
		pose_type pose;
		time_point predict_computed_time; // Time at which the prediction was computed
		time_point predict_target_time; // Time that prediction targeted.
	} fast_pose_type;

	// Using arrays as a swapchain
	// Array of left eyes, array of right eyes
	// This more closely matches the format used by Monado
	struct rendered_frame : public switchboard::event {
		std::array<GLuint, 2> texture_handles; // Does not change between swaps in swapchain
		std::array<GLuint, 2> swap_indices; // Which element of the swapchain
		fast_pose_type render_pose; // The pose used when rendering this frame.
		time_point sample_time;
		time_point render_time;
		rendered_frame() { }
		rendered_frame(std::array<GLuint, 2>&& texture_handles_, 
		               std::array<GLuint, 2>&& swap_indices_,
		               fast_pose_type render_pose_,
                       time_point sample_time_,
                       time_point render_time_)
            : texture_handles{std::move(texture_handles_)}
			, swap_indices{std::move(swap_indices_)}
			, render_pose(render_pose_)
            , sample_time(sample_time_)
            , render_time(render_time_)
        { }
	};
	
	struct hologram_input : public switchboard::event {
		int seq;
		hologram_input() { }
		hologram_input(int seq_) : seq{seq_} { }
	};

	typedef struct {
		int seq;		
	} imu_integrator_seq;

	/* I use "accel" instead of "3-vector" as a datatype, because
	this checks that you meant to use an acceleration in a certain
	place. */
	struct accel { };

	// High-level HMD specification, timewarp plugin
	// may/will calculate additional HMD info based on these specifications
	struct hmd_physical_info {
		float   ipd;
		int		displayPixelsWide;
		int		displayPixelsHigh;
		float	chromaticAberration[4];
		float	K[11];
		int		visiblePixelsWide;
		int		visiblePixelsHigh;
		float	visibleMetersWide;
		float	visibleMetersHigh;
		float	lensSeparationInMeters;
		float	metersPerTanAngleAtCenter;
	};

    struct texture_pose : public switchboard::event {
        int seq; /// TODO: Should texture_pose.seq be a long long
		duration offload_duration;
        unsigned char *image;
        time_point pose_time;
        Eigen::Vector3f position;
        Eigen::Quaternionf latest_quaternion;
        Eigen::Quaternionf render_quaternion;
        texture_pose() { }
        texture_pose(
            int seq_,
            duration offload_duration_,
            unsigned char *image_,
            time_point pose_time_,
            Eigen::Vector3f position_,
			Eigen::Quaternionf latest_quaternion_,
            Eigen::Quaternionf render_quaternion_
        ) : seq{seq_}
          , offload_duration{offload_duration_}
          , image{image_}
          , pose_time{pose_time_}
          , position{position_}
          , latest_quaternion{latest_quaternion_}
          , render_quaternion{render_quaternion_}
        { }
    };

    struct feature : public switchboard::event {
		/// Unique ID of this feature
		size_t featid;

		/// If this feature should be deleted
		bool to_delete;

		/// UV coordinates that this feature has been seen from (mapped by camera ID)
		std::unordered_map<size_t, std::vector<Eigen::VectorXf>> uvs;

		/// UV normalized coordinates that this feature has been seen from (mapped by camera ID)
		std::unordered_map<size_t, std::vector<Eigen::VectorXf>> uvs_norm;

		/// Timestamps of each UV measurement (mapped by camera ID)
		std::unordered_map<size_t, std::vector<double>> timestamps;

		/// What camera ID our pose is anchored in!! By default the first measurement is the anchor.
		int anchor_cam_id = -1;

		/// Timestamp of anchor clone
		double anchor_clone_timestamp;

		/// Triangulated position of this feature, in the anchor frame
		Eigen::Vector3d p_FinA;

		/// Triangulated position of this feature, in the global frame
		Eigen::Vector3d p_FinG;

		feature(size_t featid_, bool to_delete_, std::unordered_map<size_t, std::vector<Eigen::VectorXf>> uvs_,
				std::unordered_map<size_t, std::vector<Eigen::VectorXf>> uvs_norm_, 
				std::unordered_map<size_t, std::vector<double>> timestamps_,
				int anchor_cam_id_, double anchor_clone_timestamp_,
				Eigen::Vector3d p_FinA_, Eigen::Vector3d p_FinG_)
			: featid{featid_}
			, to_delete{to_delete_}
			, uvs{uvs_}
			, uvs_norm{uvs_norm_}
			, timestamps{timestamps_}
			, anchor_cam_id{anchor_cam_id_}
			, anchor_clone_timestamp{anchor_clone_timestamp_}
			, p_FinA{p_FinA_}
			, p_FinG{p_FinG_} 
		{ }
    };

	struct features : public switchboard::event {
		size_t size;
		time_point timestamp;
		std::vector<feature> feats;
		features(size_t size_, time_point timestamp_, std::vector<feature> feats_)
			: size{size_}
			, timestamp{timestamp_}
			, feats{feats_}
		{ }
	};
}
