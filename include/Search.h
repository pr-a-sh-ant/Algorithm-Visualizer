#pragma once

#include <functional>
#include <queue>
#include <stack>
#include "SearchSpace.h"

namespace viz::search
{
	class Search
	{
	protected:
		viz::search::SearchSpace* search_space_; // Pointer to the search space (not owned)
		float step_delay_; // Delay between steps of the search algorithm
		float step_clock_; // Time since last step of the search algorithm
		bool searching_; // True if the search algorithm is running
		bool back_tracking_; // True if the search algorithm is back tracking
		sf::Vector2i back_track_box_; // Current box being back tracked
	public:
		Search(viz::search::SearchSpace* search_space, const float step_delay);
		virtual ~Search() = default;

		// Runs a single step of the search algorithm
		virtual void run_search_step() = 0;
		// Runs a single step of back tracking
		virtual void run_back_track_step();
		// Starts the search algorithm
		virtual void start_search();

		// Setters
		void set_step_delay(const float step_delay); // Sets the delay between steps of the search algorithm

		// Getters
		[[nodiscard]]
		float get_step_delay() const; // Returns the delay between steps of the search algorithm
		[[nodiscard]]
		bool is_searching() const; // Returns true if the search algorithm is running

		virtual void update(const float& delta_time_seconds); // Updates the search algorithm
		virtual void reset(); // Resets the search algorithm states
	};

	class BreadthFirstSearch final: public Search
	{
	private:
		std::queue<sf::Vector2i> queue_;

	public:
		BreadthFirstSearch(viz::search::SearchSpace* search_space, const float step_delay);

		// Runs a single step of the search algorithm
		void run_search_step() override;
		// Starts the search algorithm
		void start_search() override;
	};

	class DepthFirstSearch final: public Search
	{
	private:
		std::stack<sf::Vector2i> stack_;

	public:
		DepthFirstSearch(viz::search::SearchSpace* search_space, const float step_delay);

		// Runs a single step of the search algorithm
		void run_search_step() override;
		// Starts the search algorithm
		void start_search() override;
	};

	class AStarSearch final: public Search
	{
	private:
		std::priority_queue<sf::Vector2i, std::vector<sf::Vector2i>, std::function<bool(const sf::Vector2i&, const sf::Vector2i&)>> priority_queue_;

	public:
		AStarSearch(viz::search::SearchSpace* search_space, const float step_delay);

		// Runs a single step of the search algorithm
		void run_search_step() override;
		// Starts the search algorithm
		void start_search() override;
	};
}
